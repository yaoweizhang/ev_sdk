mkdir -p /usr/local/ev_sdk/build
cd /usr/local/ev_sdk/build
cmake ..
make install 

mkdir -p /usr/local/ev_sdk/test/build
cd /usr/local/ev_sdk/test/build
cmake ..
make install 
cd /project/ev_sdk/test/build
./test-ji-api -f 1 -i /home/data/1233/ZDSvehicleshelmet20220712_V2_train_street_10_000141.jpg  -o /project/outputs/result.jpg
