# For a non-default SDK installation or for any Urho3D project build tree provide the actual location via URHO3D_HOME env var
if [[ -z "$URHO3D_HOME" ]]; then
    URHO3D_HOME=~/Programs/Urho3D
fi

# Const vals
PROJECTS_DIR="projects"
TEMPLATES_DIR="templates"

# Default options
TEMPLATE_DIR="minimal"
CMAKE=cmake_generic.sh

while getopts "t:d:e:n:c:u:" opt; do
    case $opt in
        t)
            TEMPLATE_DIR=$OPTARG
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

PROJECT_DIR=$PROJECTS_DIR/$PROJECT_DIR
mkdir -p $PROJECT_DIR/bin

cp -r $URHO3D_HOME/bin/CoreData/ $PROJECT_DIR/bin
cp -r $URHO3D_HOME/bin/Data/ $PROJECT_DIR/bin
cp -r $URHO3D_HOME/CMake $PROJECT_DIR/
cp -r $URHO3D_HOME/script $PROJECT_DIR/

cp CMakeLists.txt $PROJECT_DIR/
sed -i 's/MyProjectName/'$PROJECT_NAME'/g' $PROJECT_DIR/CMakeLists.txt
sed -i 's/MyExecutableName/'$PROJECT_EXEC'/g' $PROJECT_DIR/CMakeLists.txt

TEMPLATE_DIR=$TEMPLATES_DIR/$TEMPLATE_DIR
cp $TEMPLATE_DIR/* $PROJECT_DIR/

$PROJECT_DIR/script/$CMAKE $PROJECT_DIR
# $PROJECT_DIR/script/$CMAKE $PROJECT_DIR -DURHO3D_CLANG_TOOLS=1 

# Copy custom CoreData and Data
CORE_DATA=bin/CoreData
if [ -d $TEMPLATE_DIR/$CORE_DATA ]; then 
    cp -r $TEMPLATE_DIR/$CORE_DATA/* $PROJECT_DIR/$CORE_DATA/
fi
DATA=bin/Data
if [ -d $TEMPLATE_DIR/$DATA ]; then 
    cp -r $TEMPLATE_DIR/$DATA/* $PROJECT_DIR/$DATA/
fi

if [ $CMAKE == "cmake_generic.sh" ]
then
    cd $PROJECT_DIR
    make
    cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
fi
