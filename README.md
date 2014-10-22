Best Ever Ticker
================

*The ticker isn't whats important, but what it represents is.*

October is pastor appreciation month. Our pastor leads us with a servants heart
and is constantly looking toward Jesus for our Next Steps as a church...our
pastor is [Perry Noble](http://perrynoble.com). Our pastor and NewSpring Church
have a goal to reach 100,000 people in the state of South Carolina by 2020. So
what could we do that shows our pastor the appreciation we have for his vision
and his leadership? What could we do that shows *this is from the web team*?

I begin thinking about this earlier this year (2014). The idea was pretty
simple. Every name has a **number** and every **number** has a story and every
story matters to God. So what can we create that could easy
represent this and be updated automatically? So I started creating the Best Ever
Ticker; a box that display the current total of salvations at NewSpring church
since its start.

The Tech
--------

The Ticker is powered by a [Spark Core](https://spark.io); its a small
wifi-enabled microcontroller with a full RESTful API. The display is made up of
five 8x8 NeoPixel Matrices from Adafruit. It uses a small battery charger and
controller as well as a 2200mhA battery to power itself even when it isn't
plugged in.

It pulls the data from [Churchmetrics](http://churchmetrics.com) and stores them
in a small Meteor app. The app will query CM infrequently and them push the data
to the ticker when it sees the data is out of date.

The Future
----------

Its current implementation is merely a 1.0 version. The goal is that every year, for pastor appreciation month, we implement a new feature. Something that we know would be important to our pastor.

*The Best is Yet to Come!*


