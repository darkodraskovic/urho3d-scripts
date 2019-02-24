# Urho3D project setup scripts and template apps

Use `.gen_project.sh` to generate minimal, 2D or 3D app framework for Urho3D.

Script usage: `$(basename $0) -n name [-t type] [-d dir] [-e exec] [-u urho3d] [-c cmake]`.

where `type` is "minimal" "2D" or "3D", `dir` is a relative dir path, `urho3d` is a path to Urho3D source tree as cloned from Github and `cmake` is the last part (without .sh) of the Cmake scripts.
