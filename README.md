# LanguageTransfer

The Language Transfer project is committed to releasing completely free language-learning material ("the best courses money can't buy"). For more information, check out the [LT website](http://www.languagetransfer.org/).

Virtually every aspect of the project is a product of collaboration. In that vain, the source code for the (hopefully) soon-to-be-released LT app is now being open-sourced. The [Qt framework](http://www.qt.io/) is being used to make the app cross-platform. Currently, the plan is to release the app as an Android app before it is released as an iOS app (but it doesn't have to be that way!).

The app makes use of the [SoundCloud API](https://developers.soundcloud.com/docs/api/reference) to access the LT lessons that are available on that site. To contribute to the development of the LT app, first create a SoundCloud account. Then, create a client id for yourself by following [these](https://auth0.com/docs/connections/social/soundcloud) directions. Clone the LT repository (if you haven't done so already), add a file called "client_id.config" to your local repository, and paste your client id into the file.
