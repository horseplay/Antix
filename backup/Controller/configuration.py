# Configuration settings for controller

# Client settings
CLIENTS = 1
CLIENT_RUN_COMMAND = "hostname"
# the controller will cd to antix Path + this  directory and call "make":
CLIENT_BUILD_DIR = ""
CLIENT_BUILD_COMMAND = ""

# Server settings
SERVERS = 2
SERVER_RUN_COMMAND = "experiments/clock/grid.bin" # args hard-coded
SERVER_PORT = 13337
# the controller will cd to antix Path + this  directory and call "make":
SERVER_BUILD_DIR = "experiments/clock/"
SERVER_BUILD_COMMAND = "make hardeep"

# Clock settings
CLOCK_RUN_COMMAND = "experiments/clock/clock.bin" # args hard-coded
# the controller will cd to antix Path + this  directory and call "make":
CLOCK_BUILD_DIR = "experiments/clock/"
CLOCK_BUILD_COMMAND = "make clock"

# Drawer settings
DRAWER_RUN_COMMAND = "hostname"
# the controller will cd to antix Path + this  directory and call "make":
DRAWER_BUILD_DIR = ""
DRAWER_BUILD_COMMAND = ""

# Computers
CSIL_COMPUTERS = (
    'apple',
    'apricot',
    'avocado',
    'banana',
    'blackberry',
    'blueberry',
    'breadfruit',
    'cantelope',
    'cherry',
    'citron',
    'coconut',
    'cranberry',
    'currant',
    'durian',
    'fig',
    'granadilla',
    'grape',
    'guava',
    'honeydew',
    'jujube',
    'kiwi',
    'kumquat',
    'mandarin',
    'mango',
    'maypop',
    'medlar',
    'melon',
    'mulberry',
    'nectarine',
    'orange',
    'papaya',
    'peach',
    'pear',
    'pineapple',
    'plum',
    'pomelo',
    'rambutan',
    'salak',
    'tamarind',
    'tangerine',
    'amber',
    'aqua',
    'auburn',
    'azure',
    'beige',
    'black',
    'blue',
    'brown',
    'buff',
    'carmine',
    'cerise',
    'cerulean',
    'chartreuse',
    'cinnabar',
    'crimson',
    'ecru',
    'emerald',
    'gray',
    'green',
    'khaki',
    'magenta',
    'maize',
    'mauve',
    'ochre',
    'pink',
    'puce',
    'red',
    'russet',
    'scarlet',
    'sienna',
    'tan',
    'taupe',
    'teal',
    'turquoise',
    'vermillion',
    'violet',
    'white',
    'yellow',
)