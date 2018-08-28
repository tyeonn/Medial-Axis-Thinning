#include <iostream>
#include <fstream>

/**
 * @brief The ThinningSkeleton class will find the skeleton of the object by shaving the pixels on each side
 */
class ThinningSkeleton
{
public:
    ThinningSkeleton(int, int, int, int);
    void zeroFramed();
    void loadImage(std::ifstream&);
    void northThinning();
    void southThinning();
    void westThinning();
    void eastThinning();
    void prettyPrint(std::ofstream&, std::string);
    void print(std::ofstream&);
    int getCycleCount();
    void setCycleCount(int);
    bool getFlag();
    void setFlag(bool);


private:
    int numRows, numCols, minVal, maxVal, cycleCount;
    bool changeFlag = true;
    int** firstAry, ** secondAry;
    void copyAry();
    void doThinning(int, int);
    bool corner(int, int);

};

// Initialize the two 2D arrays that will hold the image
ThinningSkeleton::ThinningSkeleton(int row, int col, int min, int max)
{
    numRows = row;
    numCols = col;
    minVal = min;
    maxVal = max;
    firstAry = new int* [numRows + 2];
    secondAry = new int* [numRows + 2];
    for (int i = 0; i < numRows + 2; i++)
    {
        firstAry[i] = new int [numCols + 2];
        secondAry[i] = new int [numCols + 2];
    }
}

// Create a 1 pixel thick frame around the image
void ThinningSkeleton::zeroFramed()
{
    for (int i = 0; i < numRows + 2; i++)
    {
        for (int j = 0; j < numCols + 2; j++)
        {
            firstAry[i][j] = 0;
            secondAry[i][j] = 0;
        }
    }
}

//Load the image from the input file
void ThinningSkeleton::loadImage(std::ifstream& in)
{
    for (int i = 1; i < numRows + 1; i++)
    {
        for (int j = 1; j < numCols + 1; j++)
        {
            in >> firstAry[i][j];
        }
    }
}

//This will copy the image in the second array into the first array
void ThinningSkeleton::copyAry()
{
    for (int i = 1; i < numRows + 1; i++)
    {
        for (int j = 1; j < numCols + 1; j++)
        {
            firstAry[i][j] = secondAry[i][j];
        }
    }
}

//Prints out the image
void ThinningSkeleton::prettyPrint(std::ofstream& out, std::string direction)
{
    if (direction == "Input")
    {
        out << direction << " image: \n";
    }
    else if (direction == "Final")
    {
        out << direction << " image: \n";
    }
    else
    {
        out << "Result of cycle " << cycleCount << " after " << direction << " thinning: \n";
    }
    for (int i = 1; i < numRows + 1; i++)
    {
        for (int j = 1; j < numCols + 1; j++)
        {
            if (firstAry[i][j] > 0)
            {
                out << firstAry[i][j] << " ";
            }
            else
            {
                out << "  ";
            }
        }
        out << "\n";
    }
    out << "\n";
}

//Prints image with all the background pixels set to 0
void ThinningSkeleton::print(std::ofstream& out)
{
    out << numRows << " " << numCols << " " << minVal << " " << maxVal << "\n";
    for (int i = 1; i < numRows + 1; i++)
    {
        for (int j = 1; j < numCols + 1; j++)
        {
            out << firstAry[i][j] << " ";
        }
        out << "\n";
    }
}
int ThinningSkeleton::getCycleCount()
{
    return cycleCount;
}

void ThinningSkeleton::setCycleCount(int cycle)
{
    cycleCount = cycle;
}

bool ThinningSkeleton::getFlag()
{
    return changeFlag;
}

void ThinningSkeleton::setFlag(bool value)
{
    changeFlag = value;
    cycleCount++;
}

//Shave the top one-pixel thick layer
void ThinningSkeleton::northThinning()
{
    for (int i = 1; i < numRows + 1; i++)
    {
        for (int j = 1; j < numCols + 1; j++)
        {
            if (firstAry[i][j] > 0 && firstAry[i - 1][j] == 0)
            {
                doThinning(i, j);
            }
            else
            {
                secondAry[i][j] = firstAry[i][j];
            }
        }
    }
    copyAry();
}

//Shave bottom layer
void ThinningSkeleton::southThinning()
{
    for (int i = 1; i < numRows + 1; i++)
    {
        for (int j = 1; j < numCols + 1; j++)
        {
            if (firstAry[i][j] > 0 && firstAry[i + 1][j] == 0)
            {
                doThinning(i, j);
            }
            else
            {
                secondAry[i][j] = firstAry[i][j];
            }
        }
    }
    copyAry();
}

//Shave left layer
void ThinningSkeleton::westThinning()
{
    for (int i = 1; i < numRows + 1; i++)
    {
        for (int j = 1; j < numCols + 1; j++)
        {
            if (firstAry[i][j] > 0 && firstAry[i][j - 1] == 0)
            {
                doThinning(i, j);
            }
            else
            {
                secondAry[i][j] = firstAry[i][j];
            }
        }
    }
    copyAry();
}

//Shave right layer
void ThinningSkeleton::eastThinning()
{
    for (int i = 1; i < numRows + 1; i++)
    {
        for (int j = 1; j < numCols + 1; j++)
        {
            if (firstAry[i][j] > 0 && firstAry[i][j + 1] == 0)
            {
                doThinning(i, j);
            }
            else
            {
                secondAry[i][j] = firstAry[i][j];
            }
        }
    }
    copyAry();
}

//This will check if the pixel is a corner pixel (corner pixel is part of skeleton)
bool ThinningSkeleton::corner(int row, int col)
{
    if (firstAry[row - 1][col - 1] == 0 && firstAry[row - 1][col] == 0 && firstAry[row][col - 1] == 0)
        return true;
    if (firstAry[row - 1][col] == 0 && firstAry[row - 1][col + 1] == 0 && firstAry[row][col + 1] == 0)
        return true;
    if (firstAry[row][col + 1] == 0 && firstAry[row + 1][col] == 0 && firstAry[row + 1][col + 1] == 0)
        return true;
    if (firstAry[row][col - 1] == 0 && firstAry[row + 1][col - 1] == 0 && firstAry[row + 1][col] == 0)
        return true;
    return false;
}

//Algorithm used to see if the pixel can be shaved off or part of the skeleton
void ThinningSkeleton::doThinning(int row, int col)
{
    int pos = 0;
    int cc = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (firstAry[row + i][col + j] > 0)
            {
                pos++;
            }
        }
    }
    if (pos - 1 >= 4)
    {
        if (firstAry[row - 1][col] == 0)
            cc++;
        if (firstAry[row + 1][col] == 0)
            cc++;
        if (firstAry[row][col - 1] == 0)
            cc++;
        if (firstAry[row][col + 1] == 0)
            cc++;

        if (cc <= 1 || corner(row, col))
        {
            secondAry[row][col] = 0;
            changeFlag = true;
        }
        else
        {
            secondAry[row][col] = 1;
        }
    }
    else
    {
        secondAry[row][col] = firstAry[row][col];
    }


}
int main(int argc, char** argv)
{
    int row, col, min, max;
    std::ifstream inFile(argv[1]);
    std::ofstream outFile1(argv[2]);
    std::ofstream outFile2(argv[3]);
    inFile >> row >> col >> min >> max;

    ThinningSkeleton ts(row, col, min, max);
    ts.zeroFramed();
    ts.loadImage(inFile);
    ts.setCycleCount(0);

    while (ts.getFlag())
    {
        if (ts.getCycleCount() == 0)
            ts.prettyPrint(outFile2, "Input");
        ts.setFlag(false);
        ts.northThinning();
        if (ts.getCycleCount() == 2 || ts.getCycleCount() == 4)
            ts.prettyPrint(outFile2, "N");
        ts.southThinning();
        if (ts.getCycleCount() == 2 || ts.getCycleCount() == 4)
            ts.prettyPrint(outFile2, "S");
        ts.westThinning();
        if (ts.getCycleCount() == 2 || ts.getCycleCount() == 4)
            ts.prettyPrint(outFile2, "W");
        ts.eastThinning();
        if (ts.getCycleCount() == 2 || ts.getCycleCount() == 4)
            ts.prettyPrint(outFile2, "E");
    }

    ts.prettyPrint(outFile2, "Final");
    ts.print(outFile1);
    inFile.close();
    outFile1.close();
    outFile2.close();

    return 0;
}
