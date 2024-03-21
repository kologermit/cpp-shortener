FROM python:3.11

WORKDIR /app
RUN apt-get update
RUN apt-get install -y cmake
COPY ./requirements.txt ./requirements.txt
RUN pip install -r ./requirements.txt
RUN conan profile detect --force
COPY ./conanfile.txt ./conanfile.txt
RUN mkdir /conan
RUN conan install . --build missing -s compiler.cppstd=gnu20 --output-folder=/conan

CMD python3 ./run.py -a start