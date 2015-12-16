# Computer-Artist
Duplicate any image using a genetic, hill-climbing algorithm with OpenCV!

**Example**

Evolving Image | Original Image
:-------------:|:--------------:
![GIF](https://github.com/markasfour/Computer-Artist/blob/master/Gallery/StormtrooperEvolution.gif) | ![Stormtooper Original](https://github.com/markasfour/Computer-Artist/blob/master/Gallery/Stormtrooper.jpg)

## Install & Run
### Dependencies
OpenCV (Open Source Computer Vision) version 3.0 is the only dependency for this project.
Ensure your system has this installed prior to running this program.

### Build
Run the following in a terminal:

```
git clone http://www.github.com/markasfour/Computer-Artist.git
```

Enter the downloaded directory, build the program by running the following:

``` 
chmod u+x ./build.sh
./build.sh
``` 

After a successful build, you can now run the program!

### Command Line
When running the program, a path to an image must be provided as the first argument.
An optional second argument can be passed to specify what shape is to be used by the program.

Example:
```
./a.out Stormtrooper.jpg E
```
In this instance, the program will duplicate the `Stormtrooper.jpg` image using `Ellipses`.

Use `E` for `Ellipses`.

Use `C` for `Circles`.

Use `R` for `Rectangles`.

If no letter is passed, the program will randomly choose a shape. 

## Running Time
This program requires considerable amount of time to run from start to finish.
It is currently set to run for 10,000 generations before terminating.
The duration of each generation is mainly determined by the population size, the number of mutations, and the size of the original image.
The larger each of those variables are, the larger the total run time will be.
The population size is set to 3 while the number of mutations is set to 100.
The number of generations, the population size, and the number of mutations can all be changed by editing their global variable values in the `main.cpp` file.
It is recommended to use images with dimensions less than `1000x1000` to have a quicker run time.
The program can be stopped at any time but at the cost of a less accurate result.

The program also displays a window with the image being constructed along with all of the mutations. 
Doing so takes 1ms per mutation, also potentially slowing down the run time.
Commenting out the code could reduce the run time.

The program saves every 5th image to the computer if the constructed image is an improvement compared to the previous.
Modifying this segment to save less often or never at all can also reduce the run time.

# Gallery

Generated Image | Original Image
:--------------:|:---------------:
![Kylo Ren Generated](https://github.com/markasfour/Computer-Artist/blob/master/Gallery/KyloRen9930.jpg) | ![Kylo Ren Original](https://github.com/markasfour/Computer-Artist/blob/master/Gallery/KyloRen.jpg)
:--------------:|:---------------:
![Mona Lisa Generated](https://github.com/markasfour/Computer-Artist/blob/master/Gallery/MonaLisa9980.jpg) | ![Mona Lisa Original](https://github.com/markasfour/Computer-Artist/blob/master/Gallery/MonaLisa.jpg)
:--------------:|:---------------:
![Goku Generated](https://github.com/markasfour/Computer-Artist/blob/master/Gallery/Goku9995.jpg) | ![Goku Original](https://github.com/markasfour/Computer-Artist/blob/master/Gallery/Goku.jpg)
