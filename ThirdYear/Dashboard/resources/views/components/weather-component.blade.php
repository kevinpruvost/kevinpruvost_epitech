<div class="m-3">
    <div class="card text-red bg-danger nb-3" style="max-width: 22rem">
        <div class="card-header">
            {{$report['city_info']['name']}}
        </div>
        <div class="card-body">
            <div class="row">
                <div class="col">
                    {{$report['current_condition']['condition']}}
                </div>
                <img src="{{$report['current_condition']['icon']}}" alt="profil Pic" height="50" width="50">
            </div>
        </div>
    </div>
</div>
