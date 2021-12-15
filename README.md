# Traffic Lights Controller implementation example with C++ and fuzzylite®

## Parameters

### Input
1. Count ratio
2. Intensity ratio

### Output
1. Red signal time
2. Green signal time

## Run
Run ``make && ./fuzzycheck`` (needs ``g++5``, ``make``)

### ...with Docker:
Run ``docker build -t yanzaan/tfcontroltest . & docker run it yanzaan/tfcontroltest``

### ...with Docker-Compose:
Run ``docker-compose up --build``

## Used / Attributions / Licenses

- [fuzzylite®](https://www.fuzzylite.com) by [Juan Rada-Vilela](https://www.fuzzylite.com/jcrada), Ph.D | License: [GPL v3](http://www.gnu.org/licenses/gpl-3.0)