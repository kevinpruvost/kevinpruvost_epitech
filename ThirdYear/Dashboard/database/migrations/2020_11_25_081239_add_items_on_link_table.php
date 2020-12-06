<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\DB;
use Illuminate\Support\Facades\Schema;

class AddItemsOnLinkTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::table('links', function (Blueprint $table) {
            $table->string("refresh_token");
            $table->string("access_token");
        });

        DB::table('widgets')->insert(
            array(
                'id' => '1',
                'name' => 'Spotify',
                'key' => '0'
            )
        );
        DB::table('widgets')->insert(
            array(
                'id' => '2',
                'name' => 'Gmail',
                'key' => '0'
            )
        );
        DB::table('widgets')->insert(
            array(
                'id' => '3',
                'name' => 'Weather',
                'key' => '0'
            )
        );
        DB::table('widgets')->insert(
            array(
                'id' => '4',
                'name' => 'Youtube',
                'key' => '0'
            )
        );
        DB::table('widgets')->insert(
            array(
                'id' => '5',
                'name' => 'Coinbase',
                'key' => '0'
            )
        );
        DB::table('widgets')->insert(
            array(
                'id' => '6',
                'name' => 'CoinbaseCrypto',
                'key' => '0'
            )
        );
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        //
    }
}
