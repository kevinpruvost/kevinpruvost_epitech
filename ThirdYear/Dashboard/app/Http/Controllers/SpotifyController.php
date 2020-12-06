<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\Http;
use Illuminate\Support\Facades\Log;
use Illuminate\Support\Facades\Redirect;

class SpotifyController extends Controller
{
    protected $client_id = "eb32af9ad3ed4f9ea15159dd66efc6ab";
    protected $client_secret = "69597c433bd34c1fb663e5c1a394ff76";
    protected $redirect_uri = "http://localhost:8080/api/spotify/token";
    protected $scopes = "\'user-read-private user-read-email\'";

    protected $authorization_code = "";

    protected $access_token = "";
    protected $refresh_token = "";



    protected $pseudo = "";
    protected $user_picture = "";
    protected $artist = "";
    protected $album = "";
    protected $song = "";
    protected $cover = "";

    protected $display_name = "";
    protected $followers = "";


    /// Get Auth Code For Spotify Api
    function getAuthorisationCode() {
        if (DBController::is_access_token(Auth::id(), DBController::get_service_id('Spotify')) == false)
            return ('https://accounts.spotify.com/authorize?client_id=' . $this->client_id . '&response_type=code&redirect_uri=' . $this->redirect_uri . '&scope=user-read-playback-state');
        else
            return ('null');
    }

    /// Retrieve Auth code in Url For Spotify Api
    function getCodeFromUrl() {
        $url = url()->full();
        $parsed = parse_url($url);

        parse_str($parsed['query'], $url_args);

        return $url_args['code'];
    }

    /// Exchange Auth code for access and refresh token For Spotify Api
    function getAccessAndRefreshToken() {
        $response =  Http::asForm()->post('https://accounts.spotify.com/api/token', [
            'grant_type' => 'authorization_code',
            'code' => $this->authorization_code,
            'redirect_uri' => $this->redirect_uri,
            'client_id' => $this->client_id,
            'client_secret' => $this->client_secret,
        ]);

        $this->access_token = $response['access_token'];
        $this->refresh_token = $response['refresh_token'];

        DBController::add_row_in_link_table(Auth::id(), DBController::get_service_id('Spotify'), $this->access_token, $this->refresh_token);

        redirect::to("/dashboard");
    }

    /// Retrieve token from Db For Spotify Api
    function retrieveToken() {
        $this->access_token = DBController::get_access_token(Auth::id(), DBController::get_service_id('Spotify'));
        $this->refresh_token = DBController::get_refresh_token(Auth::id(), DBController::get_service_id('Spotify'));
    }

    /// Refresh access token For Spotify Api
    function refreshAccessToken() {
        $response =  Http::asForm()->post('https://accounts.spotify.com/api/token', [
            'grant_type' => 'refresh_token',
            'refresh_token' => $this->refresh_token,
            'client_id' => $this->client_id,
            'client_secret' => $this->client_secret,
        ]);

        $this->access_token = $response['access_token'];
        DBController::update_access_token(Auth::id(), DBController::get_service_id('Spotify'), $this->access_token);
        DBController::update_refresh_token(Auth::id(), DBController::get_service_id('Spotify'), $this->refresh_token);
    }

    /// Call an endpoint in Spotify Api to get the track data For Spotify Api
    function getCurrentTrackData($name) {
        $response = Http::withToken($this->access_token)->get('https://api.spotify.com/v1/me/player/currently-playing');

        if ($response == "")
            return;

        if (http_response_code() < 200 || http_response_code() >= 300 || $response == null ||  array_key_exists("error", json_decode($response, true))) {
            $this->refreshAccessToken();
            $this->getCurrentTrackData($name);
        } else {

            //$response = $response->json();

            $this->artist = $response['album']['artists'][0]['name'];
            $this->album = $response['album']['name'];
            $this->cover = $response['album']['images'][0]['url'];
            $this->song = $response['name'];
        }
    }

    /// Call an endpoint in Spotify Api to get the user data For Spotify Api
    function getUserData($name) {
        if ($name == "me")
            $response = Http::withToken($this->access_token)->get('https://api.spotify.com/v1/' . $name);
        else
            $response = Http::withToken($this->access_token)->get('https://api.spotify.com/v1/users/' . $name);

        if (http_response_code() < 200 || http_response_code() >= 300 || array_key_exists("error", json_decode($response, true))) {
            $this->refreshAccessToken();
            $this->getUserData($name);
        } else {

            $this->pseudo = $response['display_name'];
            if (count($response['images']) > 0)
                $this->user_picture = $response['images'][0]['url'];
            else
                $this->user_picture = null;
        }
    }

    /// link functions to get access and refresh tokens For Spotify Api
    function generateAccessAndRefreshToken() {
        ///retrieve tokens
        $this->authorization_code = $this->getCodeFromUrl();
        $this->getAccessAndRefreshToken();

        return redirect::to("/");
    }

    /// Call an endpoint in Spotify Api to get user data For Spotify Api
    function getSpecificUserDataRequest($name) {
        $response = Http::withToken($this->access_token)->get('https://api.spotify.com/v1/users/' . $name);

        if ($response == null)
            return;

        if (http_response_code() < 200 || http_response_code() >= 300 || $response == null || array_key_exists("error", json_decode($response, true))) {
            $this->refreshAccessToken();
            $this->getSpecificUserDataRequest($name);
        } else {
            $this->display_name = $response["display_name"];
            $this->followers = $response["followers"]["total"];
        }
    }

    /// Call an endpoint in Spotify Api to get user data For Spotify Api
    function getSpecificUserData($name) {
        $this->retrieveToken();
        $this->getSpecificUserDataRequest($name);

        $js = array(
            "pseudo" => $name,
            "display_name" => $this->display_name,
            "followers" => $this->followers
        );

        return response()->json([
            'success' => true,
            'data' => $js
        ]);
    }

    /// route Endpoint to retrieve data  For Spotify Api
    function getData($name = "me") {
        $this->retrieveToken();
        $this->getUserData($name);
        $this->getCurrentTrackData($name);

        $js = array(
            "pseudo" => $this->pseudo,
            "user_picture" => $this->user_picture,
            "artist" => $this->artist,
            "album" => $this->album,
            "song" => $this->song,
            "cover" => $this->cover,
        );

        return response()->json([
            'success' => true,
            'data' => $js
        ]);
    }

    ///depreciated
    function getTokenAndData() {
        ///retrieve tokens
        $this->authorization_code = $this->getCodeFromUrl();
        $this->getAccessAndRefreshToken();

        ///retrieve data
        $this->getUserData();
        $this->getCurrentTrackData();

        /// return la vue
    }
}
