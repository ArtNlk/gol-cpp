#include <thread>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <barrier>
#include <functional>
#include <random>
#include <chrono>
#include <Windows.h>

#include "gollib.h"

typedef struct workerData
{
    workerData(int _rowStart, int _rowEnd,const GOLRules& _rules, std::barrier<void (*)(void)>& _barrier):
            barrier(_barrier)
    {
        rowStart = _rowStart;
        rowEnd = _rowEnd;
        rules = _rules;
    }

    std::barrier<void (*)()>& barrier;
    int rowStart;
    int rowEnd;
    GOLRules rules;
}WorkerData;

void onCompletion();
void workerFunc(WorkerData data);

Board currentBoard;
Board prevBoard;
bool stopFlag = false;
bool flushScreen = false;
int delay = 500;
int stepsLeft;
int currentStep = 1;
char aliveChar = 219;//219 for full block
char deadChar = ' ';

/*Parameters:
    numRows
    numColumns
    numThreads
    numSteps
    ruleString
    seed
    delay
    density
 */
int main(int argc, char* argv[])
{
    std::cout << "debug\n";
    int numRows = std::stoi(argv[1]);
    int numColumns = std::stoi(argv[2]);
    int numThreads = std::stoi(argv[3]);
    int numSteps = std::stoi(argv[4]);
    GOLRules rules = GOLRules(argv[5]);
    int seed = std::stoi(argv[6]);
    delay = std::stoi(argv[7]);
    float density = std::stof(argv[8]);
    if(numRows < 1 || numColumns < 1)
    {
        throw std::invalid_argument("Invalid board size value");
    }

    if(numThreads < 1)
    {
        numThreads = (std::thread::hardware_concurrency() == 0)? 1 : std::thread::hardware_concurrency();
    }
    std::barrier<void (*)()> threadBarrier = std::barrier(numThreads,onCompletion);
    prevBoard = Board(numRows,numColumns);

    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(0.0, 1.0);
    for(int rowIndex = 0; rowIndex < prevBoard.getRowCount(); rowIndex++)
    {
        for(int colIndex = 0; colIndex < prevBoard.getColCount(); colIndex++)
        {
            prevBoard.at(rowIndex, colIndex) = dis(gen) < density;
        }
    }
    currentBoard = Board(prevBoard);

    std::cout << "Init:\n";
    std::cout << currentBoard.toCoutString(aliveChar,deadChar);
    std::chrono::milliseconds sleepDuration(1000);
    std::this_thread::sleep_for(sleepDuration);

    std::vector<std::thread> threads = std::vector<std::thread>();
    stepsLeft = numSteps;
    int rowsPerThread = std::ceil(numRows/(numThreads));
    int tailThreadRows = numRows - rowsPerThread*(numThreads-1);
    for(int i = 0; i < numThreads; i++)
    {

        if(i == numThreads - 1)
        {
            threads.emplace_back(workerFunc,WorkerData(rowsPerThread*i,rowsPerThread*i - 1 + tailThreadRows,rules, threadBarrier));
        }else
        {
            threads.emplace_back(workerFunc,WorkerData(rowsPerThread*i,rowsPerThread*(i+1) - 1,rules, threadBarrier));
        }
    }

    for(std::thread& t : threads)
    {
        t.join();
    }
    return 0;
}

void workerFunc(WorkerData data) {
    int colCount = currentBoard.getColCount();
    while(stepsLeft > 0 && !stopFlag)
    {
        for(int rowIndex = data.rowStart; rowIndex <= data.rowEnd; rowIndex++)
        {
            for(int colIndex = 0; colIndex < colCount; colIndex++)
            {
                int neighbors = prevBoard.neighborCountAt(rowIndex,colIndex);
                bool prevState = prevBoard.at(rowIndex, colIndex);
                bool newState = data.rules.shouldBeAlive(neighbors, prevState);
                currentBoard.at(rowIndex,colIndex) = newState;
            }
        }

        data.barrier.arrive_and_wait();
    }
}

void onCompletion()
{
    int rowCount = currentBoard.getRowCount();
    int colCount = currentBoard.getColCount();
    static const void* stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo((HANDLE)stdHandle, &csbi);
    int height = (csbi.srWindow.Bottom-csbi.srWindow.Top+1);
    std::string clsString(height,'\n');
    std::cout << clsString;
    std::cout << "Step " << currentStep << '\n';
    std::cout << currentBoard.toCoutString(aliveChar,deadChar);
    std::chrono::milliseconds sleepDuration(delay);
    std::this_thread::sleep_for(sleepDuration);
    currentBoard.swap(prevBoard);
    stepsLeft--;
    currentStep++;
}
