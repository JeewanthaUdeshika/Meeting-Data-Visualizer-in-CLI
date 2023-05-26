# Meeting-Data-Visualizer-in-CLI
Due to the social distancing and travel restrictions all around the world, people have moved most of the work to virtual environments. Due to this, the usage of meeting tools has exponentially increased so as the data gathered through such tools. The objective of this project is to analyze such data files and visually represent the data as per the requirement of user.

The diagram below shows the output from the program. People with most number of meetings are displayed as a horizontal bar chart.
![output1](https://github.com/JeewanthaUdeshika/Meeting-Data-Visualizer-in-CLI/assets/73388062/ca1389ef-5647-4a4b-9140-ddbbebce8ada)

There are different control and input arguments for the program. According to the arguments, the program is able to change its behaviour and result in the expected output

## Control Arguments For the Program
### File Name/ File Names
The program is able to accept any number of file names in any order. Input files should be CSV files. Also the file names will not start with ‘-’. eg: -file.csv

### Number of rows in the chart
The argument specifies the number of rows in the bar chart. It is given as −l 10 where 10 is the limit. It can be any positive integer. A number is always follow the −l argument. The pair can be in any place of the arguments list.

### Scaled option
When − − scaled argument is given, the first row of the graph should fully occupy the max print width. Any other row are scale to be matched with first row scale factor.

### Meetings/participants/duration Representation
The program can analyse three different parameters, No. of Meetings, No. of Participants and Duration. If the output is list meetings, the −m will be given. If the output is list participant counts, the −p will be given. If the output is list time duration, the −t will be given.

## Default options
The program must take at least one file name to work. All other arguments are optional. If not given, the program will work as non-scaled, will output counts for meeting and limit the output rows to 10.
