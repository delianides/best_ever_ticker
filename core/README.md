Firmware Documentation
======================

Simple steps and recomendations for compiling the firmware source.

Installation
------------

You should be able to simply compile the source code using the Spark CLI. Check https://spark.io for more details.

If you have everything required to run the spark CLI and have successfully logged in, you should be able to do run:

    spark flash <core_id> firmware

If you would like to compile and flash via USB you can run:

    spark compile firmware
    spark flash --usb firmware_XXXXXX.bin


Functions
---------

There are two functions on the ticker that you should be aware. The first is `celebrate` and it accepts a string. Right now this should only be a string of digits creating a long integar. You can test this funcation out two ways. The first via the Spark CLI:

    spark call <core_id> celebrate "42343"

Or via cURL:

    curl https://api.spark.io/v1/devices/<core_id>/celebrate \
      -d access_token="<access_token>" \
      -d "args=42322"

Note: The ticker expects the number to be greater than the previous. If its not then it returns `-1`; which essentially means error.

The other function is `reset`. This brings the number back to one. I only added this as a convience if there was ever a need to clear out the memory.

Publish
-------

The Spark API gives each core the ability to publish an event stream using `Spark.publish()`. The ticker utilizes this to let the associated web app know that its now connected to WIFI and is ready to receive data.

You can test this out using the Spark CLI by running:

    spark subscribe <core_id>

You should see events marked as `"ticker-connected"`.


