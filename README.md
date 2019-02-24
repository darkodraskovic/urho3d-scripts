# Urho3D project setup scripts and template apps

Use `.gen_project.sh` to generate minimal, 2D or 3D app framework for Urho3D.

Script usage: `$(basename $0) -n name [-t template] [-d dir] [-e exec] [-u urho3d] [-c cmake]`.

where `template` is "minimal" "2D" or "3D", `dir` is the last dir in the relative path, `urho3d` is a path to the Urho3D source tree as cloned from Github and `cmake` is a last part (afet `code_` and without `.sh`) of the Cmake scripts.
