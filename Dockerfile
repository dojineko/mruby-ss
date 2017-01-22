FROM ubuntu:latest
RUN apt-get update -qqy && apt-get -qqy install \
    build-essential \
    ruby \
    rubygems \
    wget \
    bison \
    curl \
    automake \
    libtool \
    apache2 \
    git

RUN gem install rake
ADD . /tmp/mruby-ss
WORKDIR /tmp/mruby-ss
CMD service apache2 start && rake test
