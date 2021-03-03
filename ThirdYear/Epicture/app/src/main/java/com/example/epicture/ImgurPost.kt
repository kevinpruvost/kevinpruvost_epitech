package com.example.epicture

import android.webkit.JsPromptResult
import org.json.JSONObject
import java.lang.Exception

class ImgurPost
{
    /// All the useful data of a post that we get from the api
    var id: String = ""
    var title: String = ""
    var description: String = ""
    var views: Int = 0
    var link: String = ""
    var vote: String = ""
    var ups: Int = 0
    var downs: Int = 0
    var score: Int = 0
    var favorite: Boolean = false
    var animated: Boolean = false
    var has_sound: Boolean = false

    var type: String = ""
    var cover: String = ""
    var coverLink: String = ""

    /**
     * ImgurPost constructor
     * In this constructor, we store all the data of one post to create a "post object"
     *
     */
    constructor(jsonObj: JSONObject)
    {
        val dataMap:MutableMap<Any, Any> = mutableMapOf()
        val dataNames = jsonObj.names()
        if (dataNames != null)
        {
            for (j in 0 until jsonObj.length())
            {
                val dataIndex: String = dataNames[j].toString()
                val dataValue = jsonObj.get(dataNames[j].toString())
                dataMap[dataIndex] = dataValue
            }

            id = dataMap["id"].toString()
            title = dataMap["title"].toString()
            description = dataMap["description"].toString()
            if (description.isNullOrBlank() || description == "null")
                description = "No description."

            views = dataMap["views"].toString().toInt()
            link = dataMap["link"].toString()
            vote = dataMap["vote"].toString()
            score = dataMap["score"].toString().toInt()
            ups = dataMap["ups"].toString().toInt()
            downs = dataMap["downs"].toString().toInt()
            favorite = dataMap["favorite"].toString().toBoolean()
            animated = dataMap["animated"].toString().toBoolean()
            has_sound = dataMap["has_sound"].toString().toBoolean()

            /// Get the type, located after the last '/' of dataMap["type"] value
            type = dataMap["type"].toString().substring(dataMap["type"].toString().lastIndexOf('/') + 1)
            if (type == "null" || type.isEmpty())
            {
                if (jsonObj.getJSONArray("images").length() == 0 || jsonObj.getJSONArray("images").getJSONObject(0) == null || jsonObj.getJSONArray("images").getJSONObject(0).isNull("type"))
                    throw Exception("");
                val typeTmp = jsonObj.getJSONArray("images").getJSONObject(0)["type"]
                type = typeTmp.toString().substring(typeTmp.toString().lastIndexOf('/') + 1)
            }
            /// Create the link of the image
            cover = dataMap["cover"].toString()
            coverLink = "https://i.imgur.com/" + cover + "." + type
        }
    }
}