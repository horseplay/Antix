import sys
import itertools

from configuration import *

FIRST_FREE_MACHINE = 0
GRIDS = list()

def start_process(name):
    machine, machine_ip = get_free_computer()
    if machine is None:
        print "No more free machines, exiting."
        # TODO: some code that stops all running processes across all computers
        # not exactly sure how to do this
        sys.exit()
    
    script = "ssh -f -p 24 " + USER + "@" + machine + " 'nohup " + PATH
    if name is "clock":
        script += CLOCK_RUN_COMMAND
    elif name is "client":
        script += CLIENT_RUN_COMMAND
    elif name is "server":
        script += SERVER_RUN_COMMAND + " " + str(SERVER_PORT)
    elif name is "drawer":
        script += DRAWER_RUN_COMMAND
    script += " > antix." + machine + ".out &'"
    print "Running: " + script

    try:
        out, error = run_bash_script(script)
        print "Output: " + out.rstrip()
        print
        if name is "server":
            GRIDS.append((machine, machine_ip.rstrip()))
            
    except BashScriptException as e:
        print "* ERROR STARTING " + name.upper() + " *"
        print e

def build_binary(name):
    script = "cd " + PATH
    if name is "clock":
        script += CLOCK_BUILD_DIR + "; " + CLOCK_BUILD_COMMAND
    elif name is "client":
        script += CLIENT_BUILD_DIR + "; " + CLIENT_BUILD_COMMAND
    elif name is "server":
        script += SERVER_BUILD_DIR + "; " + SERVER_BUILD_COMMAND
    elif name is "drawer":
        script += DRAWER_BUILD_DIR + "; " + DRAWER_BUILD_COMMAND
    print "Running: " + script

    try:
        out, error = run_bash_script(script)
        print "Output: " + out.rstrip()
        print
    except BashScriptException as e:
        print "* ERROR BUILDING " + name.upper() + " *"
        print e
        # stop everything!
        sys.exit()

def get_free_computer():
    """
    In the future this could check the load average on each machine
    and only return a machine based on what we deem to be free.

    For now, returns the first machine that doesn't have one of
    our processes running on it. One process per machine.
    """
    try:
        # check that the machine is up
        machine = None
        while(machine is None):
            global FIRST_FREE_MACHINE
            machine_to_test = CSIL_COMPUTERS[FIRST_FREE_MACHINE]
            FIRST_FREE_MACHINE += 1
            # get the machine's IP, and return this as well
            # if we can't get it, the machine's not connectable
            # in the future, we could also get the load average
            # and make a decision based on that
            get_machine_ip = "ssh -p 24 " + USER + "@" + machine_to_test + \
                " 'ifconfig | grep \"inet \" | grep -v 127.0.0.1 | cut -d \" \" -f12 | cut -d : -f2'"
            try:
                out, error = run_bash_script(get_machine_ip)
                # it works, return
                machine = machine_to_test
            except BashScriptException as e:
                print "* ERROR CONNECTING TO " + machine_to_test.upper() + " *"
                print e
                print "* TRYING ANOTHER MACHINE *"

        return machine, out
    except IndexError:
        return None

def run_bash_script(script, stdin=None):
    """
    Returns stderr.
    Raises an error on non-zero return code.
    """
    import subprocess
    proc = subprocess.Popen(['bash', '-c', script], stdout=subprocess.PIPE,
            stderr=subprocess.PIPE)
    stdout, stderr = proc.communicate()

    if proc.returncode:
        raise BashScriptException(proc.returncode, stderr, script)

    return stdout, stderr

class BashScriptException(Exception):
    
    def __init__(self, returncode, stderr, script):
        self.returncode = returncode
        self.stderr = stderr
        self.script = script

    def __str__(self):
        return "Returncode: " + str(self.returncode) + "\nError: " + self.stderr
        #print self.returncode
        #print self.stderr
        #return "this is the exception"

# Main:

# Get the user argument
if len(sys.argv) != 3:
    print "Usage: python controller.py <sfu_username> <path/to/antix/directory/in/your/home/directory/>"
    print "For example: python contoller.py hha13 ~/Documents/Antix/"
    print "Also, make sure you've set up SSH keys for your account."
    sys.exit()

USER = sys.argv[1]
PATH = sys.argv[2]

# Build all the code
print "*** BUILDING BINARIES ***"
print

print "** BUILDING CLOCK **"
print
build_binary("clock")

print "** BUILDING SERVER **"
print
build_binary("server")

print "** BUILDING CLIENT **"
print
build_binary("client")

print "** BUILDING DRAWER **"
print
build_binary("drawer")

# Start processes
print "*** STARTING PROCESSES ***"

# Start servers
print "** STARTING SERVERS **"
print
for _ in itertools.repeat(None, SERVERS):
    start_process("server")

# Start clock
print "** STARTING CLOCK **"
print
start_process("clock")

# Start clients
print "** STARTING CLIENTS **"
print
for _ in itertools.repeat(None, CLIENTS):
    start_process("client")

# Start drawer process
print "** STARTING DRAWER **"
print
start_process("drawer")

print GRIDS