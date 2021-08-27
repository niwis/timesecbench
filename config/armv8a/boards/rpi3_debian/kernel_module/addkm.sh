SCRIPTPATH="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"

rmmod pc_enable
insmod $SCRIPTPATH/pc_enable.ko