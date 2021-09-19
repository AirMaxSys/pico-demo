### Clone repository
```
git clone https://github.com/AirMaxSys/pico_demo.git --recurse-submodules
```
If repo had been clone:
```
git clone https://github.com/AirMaxSys/pico_demo.git
git submodules update --init --recursive
```

### Set Pico envirment varible
```
echo "export PICO_SDK_PATH=<repo path>/sdk/pico-sdk" >> ~/.bashrc
```
If you don't like set the env varible, you can pass `-DPICO_SDK_PATH=<path>` to `cmake`.


