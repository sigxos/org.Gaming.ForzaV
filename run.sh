function compile() {
    cd  "./build" || exit
    cmake ..
    make
    printf "[compile: true] \n"
}

function run() {
  gnome-terminal -- ./ForzaV
}

if [ ! -d "./build" ]; then
  mkdir "./build"
  printf "[check: true] \n"

  compile
  run
else
  compile
  run
fi


