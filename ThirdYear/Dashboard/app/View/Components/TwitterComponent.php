<?php

namespace App\View\Components;

use Illuminate\Support\Facades\Http;
use Illuminate\View\Component;

class TwitterComponent extends Component
{

    public $report = "";
    /**
     * Create a new component instance.
     *
     * @return void
     */
    public function __construct()
    {

        $response = Http::get('https://api.twitter.com/2/tweets/:1228393702244134912?tweet.fields=created_at&expansions=author_id&user.fields=created_at');

        $this->report = $response->json();
    }

    /**
     * Get the view / contents that represent the component.
     *
     * @return \Illuminate\Contracts\View\View|string
     */
    public function render()
    {
        return view('components.twitter-component');
    }
}
