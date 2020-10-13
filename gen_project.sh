# Const vals
PROJECTS_DIR="projects"
TEMPLATES_DIR="templates"

# Default options
TEMPLATE_DIR="minimal"
CMAKE=cmake_generic.sh

while getopts "t:d:n:e:c:u:" opt; do
    case $opt in
        t)
            TEMPLATE_DIR=$OPTARG
            ;;
        d)
            PROJECT_DIR=$OPTARG
            ;;
        n)
            PROJECT_NAME=$OPTARG
            ;;        
        e)
            PROJECT_EXEC=$OPTARG
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

URHO3D_DIR=/usr/local/share/Urho3D
cp -r $URHO3D_DIR/Resources/CoreData $PROJECT_DIR/bin
cp -r $URHO3D_DIR/Resources/Data/ $PROJECT_DIR/bin
ln -s $URHO3D_DIR/CMake $PROJECT_DIR/CMake

cp CMakeLists.txt $PROJECT_DIR/
sed -i 's/MyProjectName/'$PROJECT_NAME'/g' $PROJECT_DIR/CMakeLists.txt
sed -i 's/MyExecutableName/'$PROJECT_EXEC'/g' $PROJECT_DIR/CMakeLists.txt

cp gitignore $PROJECT_DIR/.gitignore

TEMPLATE_DIR=$TEMPLATES_DIR/$TEMPLATE_DIR
cp -r $TEMPLATE_DIR/* $PROJECT_DIR/

cd $PROJECT_DIR/
touch .projectile
# ln -s $URHO3D_DIR/Scripts script
cp -r $URHO3D_DIR/Scripts script
# git init
