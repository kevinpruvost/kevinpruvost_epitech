package com.example.epicture

import android.R.attr.data
import android.annotation.SuppressLint
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageButton
import android.widget.ImageView
import android.widget.TextView
import android.widget.Toast
import androidx.cardview.widget.CardView
import androidx.recyclerview.widget.RecyclerView
import com.squareup.picasso.Picasso
import okhttp3.Call
import okhttp3.Callback
import okhttp3.Response
import org.json.JSONObject
import java.io.IOException


class RecyclerAdaptater(private var imgurPosts: List<ImgurPost>):
    RecyclerView.Adapter<RecyclerAdaptater.ViewHolder>() {

    /**
     * ViewHolder
     *
     * @constructor
     *
     * get all the gui elements of an item
     * set the ressources of the image buttons
     *
     * @param itemView
     */
    inner class ViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView)
    {
        val itemTitle: TextView = itemView.findViewById(R.id.tv_title)
        val itemDescription: TextView = itemView.findViewById(R.id.tv_description)
        val itemImage: ImageView = itemView.findViewById(R.id.iv_image)
        val itemViewsText: TextView = itemView.findViewById(R.id.tv_views)
        val itemLikeText: TextView = itemView.findViewById(R.id.tv_likeNumber)
        val itemdislikeText: TextView = itemView.findViewById(R.id.tv_dislikeNumber)
        val backgroundView: CardView = itemView.findViewById(R.id.test_cardView)

        val favButton : ImageButton = itemView.findViewById<ImageButton>(R.id.iv_favorite)
        val likeButton : ImageButton = itemView.findViewById<ImageButton>(R.id.iv_like)
        val dislikeButton : ImageButton = itemView.findViewById<ImageButton>(R.id.iv_dislike)

        var faved = false
        var liked = "neutral"

        var actualToast : Toast = Toast.makeText(itemView.context, "", Toast.LENGTH_SHORT)

        init {
            /// Main Item clicked
            itemView.setOnClickListener { v: View ->
                val position = adapterPosition

            }
            favButton.setOnClickListener{
                apiPostFavorites("${imgurPosts[adapterPosition].id}")
                if (!faved)
                    favButton.setImageResource(R.drawable.favorite_on)
                else
                    favButton.setImageResource(R.drawable.favorite_off)
                faved = !faved
            }
            likeButton.setOnClickListener{
                apiPostLike("${imgurPosts[adapterPosition].id}")
                if (liked == "neutral" || liked == "down")
                {
                    likeButton.setImageResource(R.drawable.like_on)
                    dislikeButton.setImageResource(R.drawable.dislike_off)
                    liked = "up"
                }
                else
                {
                    likeButton.setImageResource(R.drawable.like_off)
                    liked = "neutral"
                }
            }
            dislikeButton.setOnClickListener{
                apiPostDislike("${imgurPosts[adapterPosition].id}")
                if (liked == "neutral" || liked == "up")
                {
                    likeButton.setImageResource(R.drawable.like_off)
                    dislikeButton.setImageResource(R.drawable.dislike_on)
                    liked = "down"
                }
                else
                {
                    dislikeButton.setImageResource(R.drawable.dislike_off)
                    liked = "neutral"
                }
            }
        }

        fun verifyFavLikeDislikeStates(id: String)
        {
            val callback = object : Callback {
                override fun onFailure(call: Call, e: IOException) {
                    Log.d("WTFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", "ERROR REQUEST FAILURE")
                }
                override fun onResponse(call: Call, response: Response) {
                    if (response.isSuccessful) {
                        if (response.code() in 200..299) {
                            callBackGetImagesInfos(response)
                        }
                    }
                    else
                    {
                        Log.d("XDDDDDDD", "Response not successful")
                    }
                }
            }
            ImgurApi.getImageInfos(callback, id)
        }

        fun callBackGetImagesInfos(response: Response)
        {
            Log.d("Image Infos", "SALUTTTTTT")

            val responseData = response.body()?.string()

            println("response data= $responseData")

            /// Turning the response to a JsonObject
            val json = JSONObject(responseData)
            if (!response.isSuccessful)
            {
                val errors = json.getJSONArray("errors").join(", ")
                throw Exception(errors)
            }

            val jsonObject: JSONObject = json.getJSONObject("data")

            if (jsonObject.getString("vote") == "up")
            {
                liked = "up"
                likeButton.setImageResource(R.drawable.like_on)
            }
            else if (jsonObject.getString("vote") == "down")
            {
                liked = "down"
                dislikeButton.setImageResource(R.drawable.dislike_on)
            }

            if (jsonObject.getBoolean("favorite"))
            {
                faved = true
                favButton.setImageResource(R.drawable.favorite_on)
            }
        }

        private fun apiPostFavorites(id: String)
        {
            val callback: Callback = object : Callback {
                override fun onFailure(call: Call, e: IOException) {}
                override fun onResponse(call: Call, response: Response) {
                    if (response.isSuccessful) {
                        if (response.code() in 200..299)
                            callbackFavoriteAction()
                    }
                }
            }

            ImgurApi.postFavorite(callback, id)
        }

        private fun apiPostLike(id: String)
        {
            val callback: Callback = object : Callback {
                override fun onFailure(call: Call, e: IOException) {}
                override fun onResponse(call: Call, response: Response) {
                    if (response.isSuccessful) {
                        if (response.code() in 200..299)
                            callbackLikeAction()
                    }
                }
            }

            ImgurApi.postLike(callback, id)
        }

        private fun apiPostDislike(id: String)
        {
            val callback: Callback = object : Callback {
                override fun onFailure(call: Call, e: IOException) {}
                override fun onResponse(call: Call, response: Response) {
                    if (response.isSuccessful) {
                        if (response.code() in 200..299)
                            callbackDislikeAction()
                    }
                }
            }

            ImgurApi.postdisLike(callback, id)
        }

        fun callbackFavoriteAction()
        {
            Log.d("Favorited", "FAVORITES EFFECT")
        }

        fun callbackLikeAction()
        {
            Log.d("Liked", "FAVORITES EFFECT")
        }

        fun callbackDislikeAction()
        {
            Log.d("Disliked", "FAVORITES EFFECT")
        }
    }

    /**
     * onCreateViewHolder
     * inflate an item (post)
     *
     * @param parent
     * @param viewType
     * @return
     */
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val v = LayoutInflater.from(parent.context).inflate(R.layout.item_layout, parent, false)

        return ViewHolder(v)
    }

    /**
     * getItemCount
     * get the number of posts instantiated in the activity
     *
     * @return
     */
    override fun getItemCount(): Int {
        return imgurPosts.size
    }


    /**
     * onBindViewHolder
     * set the data to the gui from the data stored in constructor for one item
     *
     * @param holder
     * @param position
     */
    @SuppressLint("SetTextI18n")
    override fun onBindViewHolder(holder: ViewHolder, position: Int)
    {
        holder.verifyFavLikeDislikeStates(imgurPosts[position].id)

        if (position % 2 == 1)
        {
            holder.backgroundView.setBackgroundColor(0x10000000)
        }
        /// Set the texts
        if (imgurPosts[position].title.isNullOrEmpty())
            holder.itemTitle.text = "No title"
        else
            holder.itemTitle.text = imgurPosts[position].title

        if (imgurPosts[position].description.isNullOrEmpty())
            holder.itemDescription.text = "No description"
        else
            holder.itemDescription.text = imgurPosts[position].description

        val viewsTxt = "${imgurPosts[position].views}"
        holder.itemViewsText.text = viewsTxt

        val likeTxt = "${imgurPosts[position].ups}"
        holder.itemLikeText.text = likeTxt

        val dislikeTxt = "${imgurPosts[position].downs}"
        holder.itemdislikeText.text = dislikeTxt

        if (imgurPosts[position].vote == "up")
        {
            holder.likeButton.setImageResource(R.drawable.like_on)
        }
        else if (imgurPosts[position].vote == "down")
        {
            holder.dislikeButton.setImageResource(R.drawable.dislike_on)
        }

        if (imgurPosts[position].favorite)
        {
            holder.favButton.setImageResource(R.drawable.favorite_on)
        }

        /// Load the picture
        Picasso.get()
                .load(imgurPosts[position].coverLink)
                .into(holder.itemImage)
    }
}