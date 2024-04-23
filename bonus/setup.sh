sudo rm cJSON/ -r
git clone git@github.com:DaveGamble/cJSON.git
cd cJSON/
make
cd ../
export LD_LIBRARY_PATH=$PWD/cJSON/
make re
./42sh