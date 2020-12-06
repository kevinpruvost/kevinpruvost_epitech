<?php

namespace App\Http\Controllers;

use DateTime;
use Illuminate\Http\Request;

/// Generation of the json in about.json endpoint route
class AboutController extends Controller
{
    function retJson() {
        $js = array(
            'client' => array(
                'host' => $_SERVER['REMOTE_ADDR'],
            ),
            'server' => array(
                'current_time' => (new \DateTime)->getTimestamp(),
                'services' => array(
                    array(
                        'name' => "weather",
                        'widgets' => array(
                            'name' => 'city_temperature',
                            'description' => 'Shows the weather of a city.',
                            'params' => array(
                                'name' => 'city',
                                'type' => 'string',
                            )
                        )
                    ),
                    array(
                        'name' => "youtube",
                        'widgets' => array(
                            'name' => 'youtube_channel_info',
                            'description' => 'Shows the information of a youtube channel.',
                            'params' => array(
                                'name' => 'channel_name',
                                'type' => 'string',
                            )
                        )
                    ),
                    array(
                        'name' => "coinbase",
                        'widgets' => array(
                            array(
                                'name' => 'coinbase_wallet',
                                'description' => 'Checks for your wallet\'s informations on Coinbase.',
                            ),
                            array(
                                'name' => 'coinbase_crypto',
                                'description' => 'Checks for cryptocurrencies values on Coinbase.',
                                'params' => array(
                                    'name' => 'currency',
                                    'type' => 'string',
                                )
                            )
                        )
                    ),
                    array(
                        'name' => "gmail",
                        'widgets' => array(
                            'name' => 'gmail_last_mail',
                            'description' => 'Show the last email received on your Gmail account.',
                        )
                    ),
                    array(
                        'name' => "spotify",
                        'widgets' => array(
                            array(
                                'name' => 'spotify_info',
                                'description' => 'Shows what music you are listening to.',
                            ),
                            array(
                                'name' => 'spotify_user_search',
                                'description' => 'Shows a spotify user\'s profile.',
                                'params' => array(
                                    'name' => 'username',
                                    'type' => 'string',
                                )
                            )
                        )
                    ),
                    array(
                        'name' => "love_meter",
                        'widgets' => array(
                            'name' => 'love_meter',
                            'description' => 'Shows the love compatibility between 2 persons.',
                            'params' => array(
                                array(
                                'name' => 'name_1',
                                'type' => 'string',
                                ),
                                array(
                                    'name' => 'name_2',
                                    'type' => 'string',
                                )
                            )
                        )
                    ),
                    array(
                        'name' => "covid",
                        'widgets' => array(
                            'name' => 'covid_info',
                            'description' => 'Shows statistics about the actual covid situation in France by country.',
                            'params' => array(
                                'name' => 'country',
                                'type' => 'string',
                            )
                        )
                    ),
                    array(
                        'name' => "calendar",
                        'widgets' => array(
                            'name' => 'last_event_calendar',
                            'description' => 'Show the last event in calendar on your Gmail account.',
                        )
                    ),
                )
            )
        );
        return $js;
    }
}
