Best Ever Ticker
================

*The ticker isn't whats important, but what it represents is.*

October is pastor appreciation month. Our pastor leads us with a servants heart
and is constantly looking toward Jesus for our Next Steps as a church. [Perry Noble](http://perrynoble.com) is our pastor. He and [NewSpring Church](https://newspring.cc)
have a goal to reach 100,000 people in the state of South Carolina by 2020. So
what could we do that shows him the appreciation we have for his vision
and his leadership? That shows we are thankful that we "get to" do what we love
everyday? What could we do that shows *this is from the [web
team](https://twitter.com/newspringweb)*?

I begin thinking about this earlier in the year (2014). The idea ended up being pretty
simple. We know <i>"Every name has a **number** and every **number** has a story and every
story matters to God"</i>. So what could we create that would easily
represent this and be updated automatically every week? 

So I started creating the Best Ever Ticker; a box that display the current total of salvations at NewSpring church since its start and would count all the way up to and past 100,000.

The Tech
--------

The Ticker is powered by a [Spark Core](https://spark.io); its a small
wifi-enabled microcontroller with a full RESTful API. The display is made up of
five 8x8 NeoPixel Matrices from Adafruit. It uses a small battery charger and
controller as well as a 2200mhA battery to power itself even when it isn't
plugged in.

It pulls the data from [Churchmetrics](http://churchmetrics.com) and stores it
in a small [Meteor](https://meteor.com) app. The app keeps track of all the data
and pushes a number to the ticker when it detects that the number may be out of
date. 

The Future
----------

Its current implementation is merely a 1.0 version. The goal is that every year, for pastor appreciation month, we implement a new feature. Something that we know would be important to our pastor and affirms that we are all part of this journey toward 100,000.

*The Best is Yet to Come!*


