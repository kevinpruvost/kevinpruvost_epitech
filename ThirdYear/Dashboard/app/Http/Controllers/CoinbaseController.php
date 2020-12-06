<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\Http;
use Illuminate\Support\Facades\Log;
use Illuminate\Support\Facades\Redirect;

class CoinbaseController extends Controller
{
    protected $client_id = "4bffb52d3cc259fcec5f7a61819d7a5be46b63338b1eadba4e5eeb3b94c95581";
    protected $client_secret = "2827f3bdb61ac9a24abe742baf773ceb0c45a74b2138ff3952ba4159574c7d59";
    protected $redirect_uri = "http://localhost:8080/api/coinbase/token";

    protected $authorization_code = "";

    protected $access_token = "";
    protected $refresh_token = "";



    protected $pseudo = "";
    protected $user_picture = "";
    protected $currency = "";
    protected $amount = "";

    protected $targeted_currency = "";
    protected $targeted_currency_value = "";


    /// Get Auth Code For Coinbase Api
    function getAuthorisationCode() {
        if (DBController::is_access_token(Auth::id(), DBController::get_service_id('Coinbase')) == false)
            return ('https://www.coinbase.com/oauth/authorize?response_type=code&redirect_uri=' . $this->redirect_uri . '&client_id='. $this->client_id .'&scope=wallet:accounts:read');
        else
            return ("null");
    }


    /// Retrieve Auth code in Url For Coinbase Api
    function getCodeFromUrl() {
        $url = url()->full();
        $parsed = parse_url($url);

        parse_str($parsed['query'], $url_args);

        return $url_args['code'];
    }

    /// Exchange Auth code for access and refresh token For Coinbase Api
    function getAccessAndRefreshToken() {
        $response =  Http::asForm()->post('https://api.coinbase.com/oauth/token', [
            'grant_type' => 'authorization_code',
            'code' => $this->authorization_code,
            'redirect_uri' => $this->redirect_uri,
            'client_id' => $this->client_id,
            'client_secret' => $this->client_secret,
        ]);

        //$response = $response->json();

        //echo $this->authorization_code;
        //echo json_encode($response);

        $this->access_token = $response['access_token'];
        $this->refresh_token = $response['refresh_token'];

        DBController::add_row_in_link_table(Auth::id(), DBController::get_service_id('Coinbase'), $this->access_token, $this->refresh_token);
        return redirect::to("/dashboard");
    }

    /// Refresh access token For Coinbase Api
    function refreshAccessToken() {
        $response =  Http::asForm()->post('https://api.coinbase.com/oauth/token', [
            'grant_type' => 'refresh_token',
            'refresh_token' => $this->refresh_token,
            'client_id' => $this->client_id,
            'client_secret' => $this->client_secret,
        ]);

        //$response = $response->json();

        //echo $response;

        Log::debug("çççççççççççççççççççççççççççççççççç");
        Log::debug($response);
        Log::debug("çççççççççççççççççççççççççççççççççç");

        $this->access_token = $response['access_token'];
        $this->refresh_token = $response['refresh_token'];
        DBController::update_access_token(Auth::id(), DBController::get_service_id('Coinbase'), $this->access_token);
        DBController::update_refresh_token(Auth::id(), DBController::get_service_id('Coinbase'), $this->refresh_token);
    }

    /// Call an endpoint in Coinbase Api to get wallet user data For Coinbase Api
    function getWalletData() {
        $response = Http::withToken($this->access_token)->get('https://api.coinbase.com/v2/accounts');

        //$response = $response->json();

        if (http_response_code() < 200 || http_response_code() >= 300 || array_key_exists("errors", json_decode($response, true))) {
            $this->refreshAccessToken();
            $this->getWalletData();
        } else {
            $this->currency = $response['data'][0]['balance']['currency'];
            $this->amount = $response['data'][0]['balance']['amount'];
        }
    }

    /// Retrieve token from Db For Coinbase Api
    function retrieveToken() {
        $this->access_token = DBController::get_access_token(Auth::id(), DBController::get_service_id('Coinbase'));
        $this->refresh_token = DBController::get_refresh_token(Auth::id(), DBController::get_service_id('Coinbase'));
    }

    /// Call an endpoint in Coinbase Api to get user data For Coinbase Api
    function getUserData() {

        $response = Http::withToken($this->access_token)->get('https://api.coinbase.com/v2/user');

        if (http_response_code() < 200 || http_response_code() >= 300 || array_key_exists("errors", json_decode($response, true))) {
            $this->refreshAccessToken();
            $this->getUserData();
        } else {

            $this->pseudo = $response['data']['name'];
            $this->user_picture = $response['data']['avatar_url'];
        }
    }

    /// Call an endpoint in Coinbase Api to get currency data For Coinbase Api
    function getCurrencyValue($currency, $exchangeCurrency) {
        $response = Http::get('https://api.coinbase.com/v2/prices/'. $currency . '-' . $exchangeCurrency .'/buy');

        if (http_response_code() < 200 || http_response_code() >= 300 || array_key_exists("errors", json_decode($response, true))) {
            //$this->refreshAccessToken();
            $this->getCurrencyValue($currency, $exchangeCurrency);
        } else {

            //$response = $response->json();

            $this->targeted_currency = $response['data']['currency'];
            $this->targeted_currency_value = $response['data']['amount'];
        }
        DBController::add_row_in_link_table(Auth::id(), DBController::get_service_id('Coinbase Currencies'), '3', '3');
    }

    /// link functions to get access and refresh tokens For Coinbase Api
    function generateAccessAndRefreshToken() {
        ///retrieve tokens
        $this->authorization_code = $this->getCodeFromUrl();
        $this->getAccessAndRefreshToken();

        return redirect::to("/");
    }

    /// route Endpoint to retrieve data  For Coinbase Api
    function getData() {
        $this->retrieveToken();
        $this->getUserData();
        $this->getWalletData();

        Log::debug("((((((((((((((((((((((((((((((((((((((((((((((((((");
        Log::debug(DBController::get_widgets_by_user(Auth::id()));
        Log::debug("((((((((((((((((((((((((((((((((((((((((((((((((((");

        $js = array(
            "pseudo" => $this->pseudo,
            "currency" => $this->currency,
            "amount" => $this->amount,
        );

        return response()->json([
            'success' => true,
            'data' => $js
        ]);
    }

    /// route Endpoint to retrieve currency data  For Coinbase Api
    function getCurrencyData($currency, $exchangeCurrency) {
        $this->retrieveToken();
        $this->getCurrencyValue($currency, $exchangeCurrency);

        $js = array(
            "targeted_currency" => $this->targeted_currency,
            "targeted_currency_value" => $this->targeted_currency_value,
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
        $this->getWalletData();

        /// return la vue
    }
}
