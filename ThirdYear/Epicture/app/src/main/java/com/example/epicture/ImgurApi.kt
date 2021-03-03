package com.example.epicture

import android.util.Log
import okhttp3.*
import org.json.JSONArray
import org.json.JSONObject
import java.io.IOException

class ImgurApi
{
    companion object
    {
        private val _client = OkHttpClient()

        var accessToken:     String? = ""
        var expiresIn:       String? = ""
        var tokenType:       String? = ""
        var refreshToken:    String? = ""
        var accountUsername: String? = ""
        var accountId:       String? = ""

        private var imgurUrl : String = "https://api.imgur.com"

        /**
         * postRequest
         * Method used to send POST request and react with the callback object.
         *
         * @param requestBody
         * @param apiUrl
         * @param callback
         */
        private fun postRequest(requestBody: RequestBody, apiUrl: String, callback: Callback)
        {
            val client = OkHttpClient()
            val request = Request.Builder()
                .post(requestBody)
                .url(apiUrl)
                .addHeader("Authorization", "Bearer $accessToken")
                .build()

            Log.d("Sent Post request", request.toString())
            client.newCall(request).enqueue(callback)
        }

        /**
         * getRequest
         * Method used to send GET request and react with the callback object.
         *
         * @param apiUrl
         * @param callback
         */
        private fun getRequest(apiUrl: String, callback: Callback)
        {
            val request = Request.Builder()
                .get()
                .url(apiUrl)
                .addHeader("Authorization", "Bearer $accessToken")
                .build()

            Log.d("Sent Get request", request.toString())
            _client.newCall(request).enqueue(callback)
        }

        /**
         * getMyPosts
         * Gets user's posts.
         *
         * @param callback
         */
        fun getMyPosts(callback : Callback)
        {
            val apiUrl = "$imgurUrl/3/account/$accountUsername/submissions"

            getRequest(apiUrl, callback)
        }

        /**
         * getMyFavorites
         * Gets favorite content from the user.
         *
         * @param callback
         */
        fun getMyFavorites(callback: Callback)
        {
            val apiUrl = "$imgurUrl/3/account/$accountUsername/favorites"

            getRequest(apiUrl, callback)
        }

        /**
         * getMyProfilePicture
         * Gets user's profile picture.
         *
         * @param callback
         */
        fun getMyProfilePicture(callback: Callback)
        {
            val apiUrl = "$imgurUrl/3/account/$accountUsername/avatar"

            getRequest(apiUrl, callback)
        }

        /**
         * getMyAccountData
         * Gets account data.
         *
         * @param callback
         */
        fun getMyAccountData(callback: Callback)
        {
            val apiUrl = "$imgurUrl/3/account/$accountUsername/settings"

            getRequest(apiUrl, callback)
        }

        /**
         * getImageInfos
         * Gets image (id) informations.
         *
         * @param callback
         * @param id
         */
        fun getImageInfos(callback: Callback, id: String)
        {
            val apiUrl = "$imgurUrl/3/gallery/$id"

            getRequest(apiUrl, callback)
        }

        /**
         * getGalleryPosts
         * Gets posts from gallery based on section, window, page and sorting manner.
         *
         * @param callback
         * @param section
         * @param sort
         * @param window
         * @param page
         */
        fun getGalleryPosts(callback: Callback, section: String, sort: String, window: String, page: String)
        {
            val apiUrl = "https://api.imgur.com/3/gallery/$section/$sort/$window/$page"

            getRequest(apiUrl, callback)
        }

        /**
         * getSearchGalleryPosts
         * Searches for images from gallery.
         *
         * @param callback
         * @param sort
         * @param window
         * @param page
         * @param searchQuery
         */
        fun getSearchGalleryPosts(callback: Callback, sort: String, window: String, page: String, searchQuery: String)
        {
            val apiUrl = "https://api.imgur.com/3/gallery/search/$sort/$window/$page?q=$searchQuery\n"

            getRequest(apiUrl, callback)
        }

        /**
         * postFavorite
         * Posts 'favorite' attribute on a content.
         *
         * @param callback
         * @param id
         */
        fun postFavorite(callback: Callback, id: String)
        {
            val apiUrl = "$imgurUrl/3/album/$id/favorite"
            val requestBody = RequestBody.create(MediaType.parse("application/json"), "{}")

            postRequest(requestBody, apiUrl, callback)
        }

        /**
         * postLike
         * Posts 'up' attribute on a content.
         *
         * @param callback
         * @param id
         */
        fun postLike(callback: Callback, id: String)
        {
            val apiUrl = "$imgurUrl/3/gallery/$id/vote/up"
            val requestBody = RequestBody.create(MediaType.parse("application/json"), "{}")

            postRequest(requestBody, apiUrl, callback)
        }

        /**
         * postdislike
         * Posts 'down' attribute on a content.
         *
         * @param callback
         * @param id
         */
        fun postdisLike(callback: Callback, id: String)
        {
            val apiUrl = "$imgurUrl/3/gallery/$id/vote/down"
            val requestBody = RequestBody.create(MediaType.parse("application/json"), "{}")

            postRequest(requestBody, apiUrl, callback)
        }

        fun createAlbumAndPostImage(callback: Callback, image: String, name: String, title: String, description: String, imageId: String)
        {
            val apiUrl = "$imgurUrl/3/album"

            val requestBody= MultipartBody.Builder()
                .setType(MultipartBody.FORM)
                .addFormDataPart("ids[]", "$imageId")
                .addFormDataPart("cover", "$imageId")
                .addFormDataPart("title", title)
                .addFormDataPart("privacy", "public")
                .addFormDataPart("description", description)
                .build()

            postRequest(requestBody, apiUrl, callback)
        }

        /**
         * postNewPicBase64
         * Posts an image converted in base64, with name, title and description attributed to it.
         *
         * @param callback
         * @param image
         * @param name
         * @param title
         * @param description
         */
        fun postNewPicBase64(callback: Callback, image: String, name: String, title: String, description: String)
        {
            val apiUrl = "$imgurUrl/3/upload"

            val requestBody = MultipartBody.Builder()
                .setType(MultipartBody.FORM)
                .addFormDataPart("image", image)
                .addFormDataPart("video", "")
                .addFormDataPart("album", "")
                .addFormDataPart("type", "base64")
                .addFormDataPart("name", name)
                .addFormDataPart("title", title)
                .addFormDataPart("description", description)
                .addFormDataPart("disable_audio", "0")
                .build()

            postRequest(requestBody, apiUrl, callback)
        }
    }
}