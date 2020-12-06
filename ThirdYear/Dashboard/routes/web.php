<?php

use Illuminate\Support\Facades\Redirect;
use Illuminate\Support\Facades\Route;

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get('/', function () {
    return view('dashboard');
})->middleware('auth')->middleware('verified')->name('/');

Route::get('1', function () {
    return "gentille madame";
})->middleware('auth');

Route::middleware(['auth:sanctum', 'verified'])->get('/dashboard', function () {
    return view('dashboard');
})->name('dashboard');




use App\Http\Controllers\WidgetController;
use Thujohn\Twitter\Twitter;

Route::resource('widgets', WidgetController::class)->middleware('auth');

Route::get('weather', 'WeatherController@create');

Route::get('twitter/login', 'TwitterController@twitterLogin');

Auth::routes(['verify' => true]);



use App\Http\Controllers\CoinbaseController;
use App\Http\Controllers\GmailController;
use App\Http\Controllers\CalendarController;
use App\Http\Controllers\SpotifyController;
use App\Http\Controllers\DBController;
use App\Http\Controllers\WeatherController;
use App\Http\Controllers\YoutubeController;
use App\Http\Controllers\AboutController;
use App\Http\Controllers\LoveCalculatorController;
use App\Http\Controllers\CovidController;

Route::get("/api/coinbase/auth", [CoinbaseController::class, 'getAuthorisationCode']);
Route::get("/api/coinbase/token", [CoinbaseController::class, 'generateAccessAndRefreshToken']);
Route::get("/api/coinbase/token/refresh", [CoinbaseController::class, 'refreshAccessToken']);
Route::get("/api/coinbase/data", [CoinbaseController::class, 'getData']);
Route::get("/api/coinbase/crypto/{currency}/{exchangeCurrency}", [CoinbaseController::class, 'getCurrencyData']);


Route::get("/api/gmail/auth", [GmailController::class, 'getAuthorisationCode']);
Route::get("/api/gmail/token", [GmailController::class, 'generateAccessAndRefreshToken']);
Route::get("/api/gmail/token/refresh", [GmailController::class, 'refreshAccessToken']);
Route::get("/api/gmail/data", [GmailController::class, 'getData']);

Route::get("/api/calendar/auth", [CalendarController::class, 'getAuthorisationCode']);
Route::get("/api/calendar/token", [CalendarController::class, 'generateAccessAndRefreshToken']);
Route::get("/api/calendar/token/refresh", [CalendarController::class, 'refreshAccessToken']);
Route::get("/api/calendar/data", [CalendarController::class, 'getData']);

Route::get("/api/spotify/auth", [SpotifyController::class, 'getAuthorisationCode']);
Route::get("/api/spotify/token", [SpotifyController::class, 'generateAccessAndRefreshToken']);
Route::get("/api/spotify/token/refresh", [SpotifyController::class, 'refreshAccessToken']);
Route::get("/api/spotify/data", [SpotifyController::class, 'getData']);
Route::get("/api/spotify/data/{user}", [SpotifyController::class, 'getSpecificUserData']);

Route::get("/db/insert/{widget_id}", [DBController::class, 'add_row_in_widget_order_table']);
Route::get("/db/retrieve", [DBController::class, 'get_widget_order']);

Route::get("/api/covid/{department}", [CovidController::class, 'create']);


Route::get("/api/weather/{city}", [WeatherController::class, 'create']);


Route::get("/api/love/{fperson}/{sperson}", [LoveCalculatorController::class, 'create']);


Route::get("/api/youtube/{channelName}", [YoutubeController::class, 'getChannelInfo']);


Route::get("/about.json", [AboutController::class, 'retJson']);
