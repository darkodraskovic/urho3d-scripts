# For a non-default SDK installation or for any Urho3D project build tree provide the actual location via URHO3D_HOME env var
if [[ -z "$URHO3D_HOME" ]]; then
    URHO3D_HOME=~/Programs/Urho3D
fi

PROJECT_TEMPLATE="minimal"
CMAKE=cmake_codelite.sh

while getopts "t:d:e:n:c:u:" opt; do
    case $opt in
        t)
            PROJECT_TEMPLATE=$OPTARG
            ;;
        d)
            PROJECT_DIR=$OPTARG
            ;;
        e)
            PROJECT_EXEC=$OPTARG
            ;;        
        n)
            PROJECT_NAME=$OPTARG
            ;;
        u)
            URHO3D_HOME=$OPTARG
            ;;        
        c)
            CMAKE="cmake_${OPTARG}.sh"
            ;;        
        \?)
            echo "script usage: $(basename $0) -n name [-t template] [-d dir] [-e exec] [-u urho3d] [-c cmake]" >&2
            exit 1
            ;;
        :)
            echo "Option -$OPTARG requires an argument." >&2
            exit 1
            ;;
    esac
done

if [ -z "$PROJECT_NAME" ]
then
    echo "ERROR: The project name not specified."
    exit 1
fi

if [ -z "$PROJECT_DIR" ]
then
    PROJECT_DIR=$PROJECT_NAME
fi

PROJECT_EXEC=$PROJECT_NAME

mkdir -p $PROJECT_DIR/bin

cp -r $URHO3D_HOME/bin/CoreData/ $PROJECT_DIR/bin
cp -r $URHO3D_HOME/bin/Data/ $PROJECT_DIR/bin
ln -s $URHO3D_HOME/CMake $PROJECT_DIR/
ln -s $URHO3D_HOME/script $PROJECT_DIR/

cp CMakeLists.txt $PROJECT_DIR/
sed -i 's/MyProjectName/'$PROJECT_NAME'/g' $PROJECT_DIR/CMakeLists.txt
sed -i 's/MyExecutableName/'$PROJECT_EXEC'/g' $PROJECT_DIR/CMakeLists.txt

cp $PROJECT_TEMPLATE/* $PROJECT_DIR/

$PROJECT_DIR/script/$CMAKE $PROJECT_DIR

if [ $CMAKE == "cmake_generic.sh" ]
then
    cmake $PROJECT_DIR -DCMAKE_EXPORT_COMPILE_COMMANDS=1
fi
