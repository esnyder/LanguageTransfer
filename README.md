# LanguageTransfer

The Language Transfer project is committed to releasing completely free language-learning material ("the best courses money can't buy"). For more information, check out the [LT website](http://www.languagetransfer.org/).

Virtually every aspect of the project is a product of collaboration. In that vain, the source code for the (hopefully) soon-to-be-released LT app is now being open-sourced. The [Qt framework](http://www.qt.io/) is being used to make the app cross-platform. Currently, the plan is to release the app as an Anroid app before it is released as an iOS app (but it doesn't have to be that way!).

The app makes use of the [SoundCloud API](https://developers.soundcloud.com/docs/api/reference) to access the LT lessons that are available on that site. To develop, first create a SoundCloud account and create a client id for yourself by following [these](https://auth0.com/docs/connections/social/soundcloud) directions. Once you've cloned the LT repository, paste the generated client id into the client_id.config file.
