# ekpassword
Ek Password Manager

Components
===

- **ekstore** This is a native library written on top of OpenSSL, that is used to 
read and write password and related login information to a persistent file in encrypted manner. This library could be 
used by other components like `ekserver` or iOS/Android apps
*Status: Partially implemented**
    
- **ekserver** This will be an OpenSSL server that will provide a REST API. It will run in the background and
will have interface through an icon in the operating system's Tray. The browser plugins will talk to this
server to query for login information for given website. This server will only listen on localhost. 
*Status: Not implemented yet*

- **Browser extensions** The extensions for Chrome, Firefox, etc. will be responsible for detecting login fields
on current webpage and querying the login information from `ekserver`. They will also implement other goodies like
password generation.
*Status: Not implemented yet*

- **Mobile apps** iOS/Android apps could be written that will interact with Dropbox. User is assumed to have saved the
ekstore-managed file in a Dropbox folder. The app can use Dropbox's API to read/write such file from the mobile device.
It will use the native `ekstore` library to read/write in secure fashion.
*Status: Not implemented yet*

Build instructions
===

    git clone git@github.com:bluemathsoft/ekpassword.git
    
    # How to build ekstore library
    cd ekpassword/ekstore
    mkdir build
    cd build
    cmake ..
    make
    
Dependencies
===

You will need OpenSSL and CppUnit to build `ekstore`.

* Ubuntu

`sudo apt install libssl-dev libcppunit-dev`
    
* Mac OSX

Use `brew` to install necessary packages. Refer to CMakeLists.txt in case of issues.
