while getopts "n:" opt; do
    case $opt in
        n)
            FACTORY_NAME=$OPTARG
            ;;
        \?)
            echo "script usage: $(basename $0) -n name" >&2
            exit 1
            ;;
        :)
            echo "Option -$OPTARG requires an argument." >&2
            exit 1
            ;;
    esac
done

if [ -z "$FACTORY_NAME" ]
then
    echo "ERROR: The factory name not specified."
    exit 1
fi

# .h
FACTORY_H=${FACTORY_NAME}.h
cp Factory.h $FACTORY_H

FACTORY_UPPERCASE=$(echo $FACTORY_NAME | tr a-z A-Z)
sed -i 's/FACTORY/'$FACTORY_UPPERCASE'/g' $FACTORY_H

sed -i 's/Factory/'$FACTORY_NAME'/g' $FACTORY_H

# .cpp
FACTORY_CPP=${FACTORY_NAME}.cpp
cp Factory.cpp $FACTORY_CPP
sed -i 's/Factory/'$FACTORY_NAME'/g' $FACTORY_CPP
