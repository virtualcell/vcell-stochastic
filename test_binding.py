import vcellstochastic_py

def test_binding():
    print("Testing VCell Stochastic Python Binding...")
    
    # Test StochModel
    model = vcellstochastic_py.StochModel()
    print(f"StochModel created. Num vars: {model.getNumOfVars()}")
    assert model.getNumOfVars() == 0
    
    # Test Gibson
    gibson = vcellstochastic_py.Gibson()
    print(f"Gibson created. Num vars: {gibson.getNumOfVars()}")
    assert gibson.getNumOfVars() == 0
    
    # Test random uniform
    r = gibson.getRandomUniform()
    print(f"Random uniform value: {r}")
    assert 0 <= r <= 1
    
    # Test MultiTrialStats
    stats = vcellstochastic_py.MultiTrialStats(2, 5)
    print(f"MultiTrialStats created. Num vars: {stats.getNumVars()}, Num time points: {stats.getNumTimePoints()}")
    assert stats.getNumVars() == 2
    
    stats.startNewTrial()
    stats.addSample(0, 0.0, [1.0, 2.0])
    print(f"Mean at t=0, var=0: {stats.getMean(0, 0)}")
    assert stats.getMean(0, 0) == 1.0
    
    print("All basic binding tests passed!")

if __name__ == "__main__":
    test_binding()
