#ifndef RESULT_H
#define RESULT_H

enum Result
{
    Success = 0,

    CommandFileNotExist = 100,
    LoadFileNotExist,

    VertexKeyNotExist = 200,
    InvalidVertexKey,
    GraphNotExist,
    InvalidAlgorithm,
    NegativeCycleDetected,

    InvalidAlgorithmName = 001,
    InvalidOptionName = 003,
    FaildtoUpdatePath = 005,

    NonDefinedCommand = 300,

    //���ī�� Result ����
    None=400,
    Fivesame,
    Tensame,
    Wordsame,


};

#endif