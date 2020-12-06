<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\DB;

class DBController extends Controller
{
    public static function is_access_token($user_id, $widget_id) {
        $row = DB::table('links')->where('user_id', '=', $user_id)->where('widget_id', '=', $widget_id)->first();

        if ($row == null || $row == '') {
            return false;
        } else {
            return true;
        }
    }

    public static function remove_row_in_link_table($user_id, $widget_id){

        DB::table('links')->where('user_id', '=', $user_id)->where('widget_id', '=', $widget_id)->delete();
    }

    public static function update_access_token($user_id, $widget_id, $access_token) {
        DB::table('links')->where('user_id', '=', $user_id)->where('widget_id', '=', $widget_id)->update(array('access_token' => $access_token));
    }

    public static function update_refresh_token($user_id, $widget_id, $refresh_token) {
        DB::table('links')->where('user_id', '=', $user_id)->where('widget_id', '=', $widget_id)->update(array('refresh_token' => $refresh_token));
    }

    public static function get_widgets_by_user($user_id) {
        return db::table('links')->where('user_id', '=', $user_id)->get();
    }

    public static function add_row_in_link_table($user_id, $widget_id, $access_token, $refresh_token) {

        /// try retrieve row
        $row = DB::table('links')->where('user_id', '=', $user_id)->where('widget_id', '=', $widget_id)->first();

        if ($row == null ||$row == '') {
            DB::insert('insert into links (user_id, widget_id, access_token, refresh_token) values(?, ?, ?, ?)',[$user_id, $widget_id, $access_token, $refresh_token]);
        }
        else {
            DB::table('links')->where('user_id', '=', $user_id)->where('widget_id', '=', $widget_id)->update(['access_token' => $access_token]);
            DB::table('links')->where('user_id', '=', $user_id)->where('widget_id', '=', $widget_id)->update(['refresh_token' => $refresh_token]);
        }
    }

    public static function get_access_token($user_id, $service_id) {
        return DB::table('links')->where('user_id', '=', $user_id)->where('widget_id', '=', $service_id)->value('access_token');
    }
    public static function get_refresh_token($user_id, $service_id) {
        return DB::table('links')->where('user_id', '=', $user_id)->where('widget_id', '=', $service_id)->value('refresh_token');
    }

    public static function get_service_id($service_name) {
        return substr(DB::table('widgets')->where('name', '=', $service_name)->pluck('id'), 1, -1);
    }

    public static function add_row_in_widget_order_table($widget_order) {
        $user_id = Auth::id();

        /// try retrieve row
        $row = DB::table('widgetOrder')->where('user_id', '=', $user_id)->first();

        if ($row == null || $row == '') {
            DB::insert('insert into widgetOrder (user_id, widget_order) values(?, ?)',[$user_id, $widget_order]);
        }
        else {
            DB::table('widgetOrder')->where('user_id', '=', $user_id)->update(['widget_order' => $widget_order]);
        }
    }

    public static function get_widget_order() {
        return DB::table('widgetOrder')->where('user_id', '=', Auth::id())->value('widget_order');
    }
}
