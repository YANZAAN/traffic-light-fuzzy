# Traffic Light Controller implementation example with C++ and fuzzylite®
In 1965, the American mathematician Lotfi Zade put the fuzzy sets theory to scientific community. It formed the basis of the corresponding logic

Initially this paradigm was perceived coldly due to differences with Aristotelian logic. However, in the future it'll stand like a basis for many other specified embedded systems
  
This is an automated traffic control system based on fuzzy logic principle (so called fuzzy interference system - FIS)

## Parameters
### Input linguistic variables (strict: <β, T, X>)
1. <Count ratio, (low, medium, high), 0..100%>
2. <Intensity ratio, (low, medium, high), 0..100%>

### Output linguistic variables (strict: <β, T, X>)
1. <Red signal time, (low, medium, high), 20..90s>
2. <Green signal time, (low, medium, high), 20..90s>

## Usage and restrictions
Made with educational purpose. Free to use, modify etc.

## Run
Run ``make && ./fuzzycheck`` (needs ``g++5``, ``make``)

### ...with Docker:
Run ``docker build -t yanzaan/tfcontroltest . & docker run it yanzaan/tfcontroltest``

### ...with Docker-Compose:
Run ``docker-compose up --build``

## Further research
1. Trying different accessory functions and combinations (gussians, bells, triangles etc.)

## Used / Attributions / Licenses

- [fuzzylite®](https://www.fuzzylite.com) by [Juan Rada-Vilela](https://www.fuzzylite.com/jcrada), Ph.D | License: [GPL v3](http://www.gnu.org/licenses/gpl-3.0)
