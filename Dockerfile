FROM fuzzylite/fuzzylite:6.0

ARG CXX_COMPILER=g++
ENV CXX_COMPILER ${CXX_COMPILER}

RUN apt-get update && \
    apt-get -y install ${CXX_COMPILER} 

WORKDIR app

COPY . .

RUN make

CMD ./fuzzycheck
