# Modular driver for Raspberry PI 3B
This is a simple modular driver for the Raspberry PI 3B that implements the usage of GPIO to interface with an external module.

# Using the driver code
## Compiling the driver
To compile the driver module run `make` in the build directory.

## Testing the driver
### Loading the driver using the script
To load the driver module using the provided script use the following command:
```
sudo sh gpiodriverRun.sh 1 0
```
To enable tail output set the second parameter to '1'
```
sudo sh gpiodriverRun.sh 1 1
```

### Loading the driver Without the script
To load the driver module without the use of the script use the following command:
```
sudo nsmod GpioDriverMod.ko
```

### Unloading the driver using the script
To unload the driver module using the provided script use the following command:
```
sudo sh gpiodriverRun.sh 2 0
```
To enable tail output set the second parameter to '1'
```
sudo sh gpiodriverRun.sh 2 1
```

### Loading the driver without the script
To load the driver module without the use of the script use the following command:
```
sudo rmmod GpioDriverMod.ko
```

### Script input options
The list of possible input/parameter combinations for the script are as follows:
```
sudo sh gpiodriverRun.sh x y
```
* Parameter 1 (x):
   * 0 : dmesg
   * 1 : Load module
   * 2 : Unload module
   * 3 : Load and unload moule
* Parameter 2 (y):
  * 0 : desable tail
  * 1 : enable tail

The above list can be obtained by running the following command:
```
sudo sh gpiodriverRun.sh
```

## Intalling the driver
To load the driver and generate the driver file automatically run the following command in the build directory.
```
sudo make install
````

## Unintalling the driver
To unload the driver and remove the driver file automatically run the following command in the build directory.
```
sudo make uninstall
````

# Installing the Kernel Headers
In order to compile and work with drivers it is required to ensure that the Kernel headers are installed. This can be done by following the steps in the guide provided in the below link.

https://www.tecmint.com/install-kernel-headers-in-ubuntu-and-debian/
