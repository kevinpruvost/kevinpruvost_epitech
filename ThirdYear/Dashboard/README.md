# Dashboard

The purpose of this project for us was to familiarize with the software platform we've chosen (Laraval & React js), we could chose other technologies like Java, .NET, node.js and many others used for our backend, frontend or the two of them.

So, to learn that, we had to go through the creation of a dashboard. To do this, we needed to implement a web application that works like [Netvibes](https://www.netvibes.com/en).

Basically, you need to log on our application and after that, you will have access to multiple widgets. These widgets use API that we also had to chose.
They all have a practical purpose that we must have made the most easy to use possible. 

## Backend

<p align="center"><a href="https://laravel.com" target="_blank"><img src="https://raw.githubusercontent.com/laravel/art/master/logo-lockup/5%20SVG/2%20CMYK/1%20Full%20Color/laravel-logolockup-cmyk-red.svg" width="400"></a></p>

<p align="center">
<a href="https://travis-ci.org/laravel/framework"><img src="https://travis-ci.org/laravel/framework.svg" alt="Build Status"></a>
<a href="https://packagist.org/packages/laravel/framework"><img src="https://img.shields.io/packagist/dt/laravel/framework" alt="Total Downloads"></a>
<a href="https://packagist.org/packages/laravel/framework"><img src="https://img.shields.io/packagist/v/laravel/framework" alt="Latest Stable Version"></a>
<a href="https://packagist.org/packages/laravel/framework"><img src="https://img.shields.io/packagist/l/laravel/framework" alt="License"></a>
</p>

## Frontend

<p align="center"><a href="https://fr.reactjs.org/tutorial/tutorial.html" target="_blank"><img src="https://www.ubidreams.fr/wp-content/uploads/2020/06/logo-react-js.png" width="400"></a></p>

## Widgets

| Widget | Description | API used |
| ------------- | ------------- | --------- |
| Coinbase Wallet | Checks for your wallet's informations on Coinbase.  | [Coinbase] |
| Coinbase Cryptocurrencies | Checks for cryptocurrencies values on Coinbase.  | [Coinbase] |
| Weather | Shows the weather of a city.  | [Previsions-Meteo] |
| Gmail | Show the last email received on your Gmail account.  | [GMail] |
| Spotify Account | Shows what music you are listening to.  | [Spotify] |
| Spotify User Search | Shows a spotify user's profile.  | [Spotify] |
| Youtube | Shows the informations of a youtube channel.  | [Youtube] |
| Love Meter | Shows the love compatibility between 2 persons.  | [Love Meter] |
| Covid Infos | Shows statistics about the actual covid situation in France by county. | [Covid] |
| Calendar | Show next event in user's calendar | [Calendar] |

[Coinbase]: https://developers.coinbase.com/api/v2
[Previsions-Meteo]: https://www.prevision-meteo.ch/uploads/pdf/recuperation-donnees-meteo.pdf
[GMail]: https://developers.google.com/gmail/api/reference/rest
[Spotify]: https://developer.spotify.com/documentation/web-api/reference/
[Youtube]: https://developers.google.com/youtube/v3/docs
[Love Meter]: https://rapidapi.com/ajith/api/love-calculator/endpoints
[Covid]: https://github.com/florianzemma/CoronavirusAPI-France
[Calendar]: https://developers.google.com/calendar/v3/reference

## Requirements

You will need these softwares in order to build this project.

### docker / docker-compose

> [Docker Desktop](https://docs.docker.com/docker-for-windows/install/) for Windows.

> [docker](https://docs.docker.com/engine/install/ubuntu/) for Ubuntu.
> [docker-compose](https://docs.docker.com/compose/install/) for Ubuntu.

### npm

> [npm](https://www.npmjs.com/get-npm) for Windows.

> [npm](https://doc.ubuntu-fr.org/nodejs) for Ubuntu.

### composer

> [composer](https://getcomposer.org/download/) for both Operating Systems.

### Laravel

> [Laravel](https://laravel.com/docs/8.x/installation) for both Operating Systems.

## Build & Launch

Just launch these commands in order to get on the dashboard.

### Build

> **composer install**

> **npm install** (you will maybe need to run it with admin permissions)

> **docker build .**

> **npm run dev** (you will maybe need to run it with admin permissions)

### Launch

> **docker-compose up -d --build**

> Launch just once at the creation of the server : **docker exec app php artisan migrate**

Now that it is launched, you just have to go on [localhost](http://localhost) to get on the dashboard and enjoy our widgets !

If you want to close the server, then just launch : 

> **docker-compose down**
