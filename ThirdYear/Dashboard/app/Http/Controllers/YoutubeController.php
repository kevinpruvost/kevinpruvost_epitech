<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\Http;
use Illuminate\Support\Facades\Redirect;

class YoutubeController extends Controller
{
    protected $api_key = "AIzaSyDGM3U5SIJtIAK8XbYNySllwMNntGIbY3k";


    protected $subs = "";
    protected $videoCount = "";
    protected $viewCount = "";


    function getChannelId($channelName) {
        DBController::add_row_in_link_table(Auth::id(), DBController::get_service_id('Youtube'), '1', '1');
        $api = Http::get('https://www.googleapis.com/youtube/v3/search?part=snippet&type=channel&fields=items%2Fsnippet%2FchannelId&q='. $channelName .'&key=' . $this->api_key);

        $api = $api->json();

        return $api['items'][0]['snippet']['channelId'];
    }

    /// route Endpoint to retrieve data  For Youtube Api
    function getChannelInfo($channelName) {

        $channelId = $this->getChannelId($channelName);

        $api = Http::get('https://www.googleapis.com/youtube/v3/channels?part=statistics&id='.$channelId.'&key=' . $this->api_key);

        $api = $api->json();

        $this->subs = $api['items'][0]['statistics']['subscriberCount'];
        $this->videoCount = $api['items'][0]['statistics']['videoCount'];
        $this->viewCount = $api['items'][0]['statistics']['viewCount'];

        $api = Http::get('https://www.googleapis.com/youtube/v3/channels?id='. $channelId .'&part=snippet&key=' . $this->api_key);

        $js = array(
            "subs" => $this->subs,
            "videoCount" => $this->videoCount,
            "viewCount" => $this->viewCount,
            "title" => $api['items'][0]['snippet']['title'],
            "description" => $api['items'][0]['snippet']['description'],
            "avatar_cover" => $api['items'][0]['snippet']['thumbnails']['default']['url'],
            "country" => (array_key_exists('country', $api['items'][0]['snippet']) ? $api['items'][0]['snippet']['country'] : null),
            "channel_link" => "https://www.youtube.com/" . ((array_key_exists('customUrl', $api['items'][0]['snippet'])) ? $api['items'][0]['snippet']['customUrl'] : $api['items'][0]['snippet']['title']),
        );

        return response()->json([
            'success' => true,
            'data' => $js
        ]);
    }
}
