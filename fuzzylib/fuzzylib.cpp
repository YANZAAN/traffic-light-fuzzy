#include "fuzzylib.hpp"

using namespace fuzzylib;
using namespace std;

Engine* TLEngine::create()
{
    /* ------------------- Defining engine ------------------- */
    Engine *engine = new Engine;
    engine->setName("Traffic Light Control");
    engine->setDescription("");

    /* ------------------- Defining input variables ------------------- */
    InputVariable *countRatio = new InputVariable,
                  *intensityRatio = new InputVariable;

    /* ------------------- Defining output variables ------------------- */
    OutputVariable *redSignalTime = new OutputVariable,
                   *greenSignalTime = new OutputVariable;

    /* ------------------- Parametrizing ------------------- */
    countRatio->setName("count_ratio");
    intensityRatio->setName("intensity_ratio");

    redSignalTime->setName("red_signal_time");
    greenSignalTime->setName("green_signal_time");

    scalar inputMin = 0.00,
           inputMax = 100.00,
           outputMin = 20.00,
           outputMax = 90.00;

    countRatio->setEnabled(true);
    intensityRatio->setEnabled(true);

    redSignalTime->setEnabled(true);
    greenSignalTime->setEnabled(true);

    countRatio->setRange(inputMin, inputMax);
    intensityRatio->setRange(inputMin, inputMax);

    redSignalTime->setRange(outputMin, outputMax);
    greenSignalTime->setRange(outputMin, outputMax);

    countRatio->setLockValueInRange(true);
    intensityRatio->setLockValueInRange(true);

    redSignalTime->setLockValueInRange(true);
    greenSignalTime->setLockValueInRange(true);

    countRatio->addTerm(new Gaussian("low", 25.00, 7.00));
    countRatio->addTerm(new Gaussian("medium", 50.00, 7.00));
    countRatio->addTerm(new Gaussian("high", 75.00, 7.00));

    intensityRatio->addTerm(new Gaussian("low", 25.00, 7.00));
    intensityRatio->addTerm(new Gaussian("medium", 50.00, 7.00));
    intensityRatio->addTerm(new Gaussian("high", 75.00, 7.00));

    redSignalTime->addTerm(new Gaussian("low", 31.67, 4.90));
    redSignalTime->addTerm(new Gaussian("medium", 53.34, 4.90));
    redSignalTime->addTerm(new Gaussian("high", 75.00, 4.90));

    greenSignalTime->addTerm(new Gaussian("low", 31.67, 4.90));
    greenSignalTime->addTerm(new Gaussian("medium", 53.34, 4.90));
    greenSignalTime->addTerm(new Gaussian("high", 75.00, 4.90));

    redSignalTime->setDefaultValue(outputMin);
    redSignalTime->setLockPreviousValue(false);

    greenSignalTime->setDefaultValue(outputMin);
    greenSignalTime->setLockPreviousValue(false);

    //Range: Maximum, AlgebraicSum, BoundedSum, DrasticSum, EinsteinSum, HamacherSum, NilpotentMaximum, NormalizedSum
    redSignalTime->setAggregation(new Maximum);
    greenSignalTime->setAggregation(new Maximum);

    //Range: Bisector, Centroid, IntegralDefuzzifier, LargestOfMaximum, MeanOfMaximum, SmallestOfMaximum, WeightedAverage, WeightedDefuzzifier
    redSignalTime->setDefuzzifier(new Centroid);
    greenSignalTime->setDefuzzifier(new Centroid);

    engine->addInputVariable(countRatio);
    engine->addInputVariable(intensityRatio);

    engine->addOutputVariable(redSignalTime);
    engine->addOutputVariable(greenSignalTime);

    /* ------------------- Creating rule book ------------------- */
    RuleBlock *rules = new RuleBlock;
    rules->setName("Rule Book");
    rules->setDescription("");
    rules->setEnabled(true);

    /* ------------------- Inserting rules ----------------- */
    rules->setConjunction(new Minimum);
    rules->setDisjunction(new Maximum);
    rules->setImplication(new Minimum);
    rules->setActivation(new General);

    /* 1 */ rules->addRule(Rule::parse(
        "if count_ratio is low and intensity_ratio is low then red_signal_time is high and green_signal_time is low", engine));
    /* 2 */ rules->addRule(Rule::parse(
        "if count_ratio is low and intensity_ratio is medium then red_signal_time is medium and green_signal_time is medium", engine));
    /* 3 */ rules->addRule(Rule::parse(
        "if count_ratio is low and intensity_ratio is high then red_signal_time is medium and green_signal_time is medium", engine));
    /* 4 */ rules->addRule(Rule::parse(
        "if count_ratio is medium and intensity_ratio is low then red_signal_time is medium and green_signal_time is low", engine));
    /* 5 */ rules->addRule(Rule::parse(
        "if count_ratio is medium and intensity_ratio is medium then red_signal_time is medium and green_signal_time is medium", engine));
    /* 6 */ rules->addRule(Rule::parse(
        "if count_ratio is medium and intensity_ratio is high then red_signal_time is low and green_signal_time is medium", engine));
    /* 7 */ rules->addRule(Rule::parse(
        "if count_ratio is high and intensity_ratio is low then red_signal_time is medium and green_signal_time is medium", engine));
    /* 8 */ rules->addRule(Rule::parse(
        "if count_ratio is high and intensity_ratio is medium then red_signal_time is medium and green_signal_time is medium", engine));
    /* 9 */ rules->addRule(Rule::parse(
        "if count_ratio is high and intensity_ratio is high then red_signal_time is low and green_signal_time is high", engine));
    engine->addRuleBlock(rules);

    return engine;
}

tuple<scalar, scalar> TLEngine::run(Engine* engine, tuple<scalar, scalar> input)
{
    if (!engine->isReady())
    {
        throw Exception("Kernel isn't ready!");
        return make_tuple(NULL, NULL);
    }

    InputVariable *countRatio = engine->getInputVariable("count_ratio"),
                  *intensityRatio = engine->getInputVariable("intensity_ratio");
    OutputVariable *redSignalTime = engine->getOutputVariable("red_signal_time"),
                   *greenSignalTime = engine->getOutputVariable("green_signal_time");
    
    scalar firstInputScalar, secondInputScalar;
    tie(firstInputScalar, secondInputScalar) = input;

    countRatio->setValue(firstInputScalar);
    intensityRatio->setValue(secondInputScalar);

    engine->process();

    return make_tuple(redSignalTime->getValue(), greenSignalTime->getValue());
}

void TLEngine::test(Engine* engine, short testCount)
{
    if (testCount <= 0) {
        throw Exception("Primary test counter is less than zero (or equal to it)");
        return;
    }

    int countRatioMaxima = (int)engine->getInputVariable("count_ratio")->getMaximum(),
        intensityRatioMaxima = (int)engine->getInputVariable("intensity_ratio")->getMaximum();

    int countRatioInput, intensityRatioInput;
    int redSignalTimeOutput = INT16_WIDTH,
        greenSignalTimeOutput = INT16_WIDTH;

    for (short i = 0; i < testCount; i++) {
        countRatioInput = rand() % countRatioMaxima;
        intensityRatioInput = rand() % intensityRatioMaxima;

        try
        {
            tie(redSignalTimeOutput, greenSignalTimeOutput) = TLEngine::run(
                engine,
                make_tuple(countRatioInput, intensityRatioInput)
            );
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return;
        }

        cout << "---------Test № " << to_string(i) << "---------" << endl;
        cout << "Input: Count Ratio (" << countRatioInput << "), Intensity Ratio (" << intensityRatioInput << ")" << endl;
        cout << "Output: Red Signal Timing = " << redSignalTimeOutput << ", Green Signal Timing = " << greenSignalTimeOutput << endl;
    }
}