## Motion Estimation ##

The pupose of this project was to create a Motion Estimation program that would take two image files as input and calculate the motion estimation vectors for each block of the image using the sum of absolute differences.  The goal of the program was to reduce runtime as much as possible using a variety of techniques while still 

### What I Did ###

The project work was about evenly split between myself and my partner for the project, and the both of us touched on most aspects of the project.  We generated the test images, worked out the theory, implemented the algorithm and other necessary methods, then implemented a variety of techniques such as software pipelining, memory management, and register management to try to reduce the runtime of the algorithm as much as possible. 

### Methodology ###

To approach this project, we decided that the first and most important step would be to get a good understanding of the algorithm and our requirements.  Through this process, we learned that we needed to have two 320 x 240 greyscale images of an easily readible format with pixel values between 0 and 255 in order to work the best with 8-bit operations.  We also learned that the biggest time problems facing us would be the memory management of needing to repeatedly access so many blocks across large martices and the actual runtime of each sum of absolute differences calculation.  So, our first step was to come up with a rough and unrefined functional version of the algorithm, and then start to add efficiencies where possible.

Once we had decided upon using the pgm image file type with 8-bit pixel values, it was easy enough to read the image files and load them into expansive matrices, as seen in the input() and main() functions.  We did not prioritize efficiency as much in these steps, as they only needed to run once, as opposed to the thousands of times that the sum of absolute differences would be run.    
