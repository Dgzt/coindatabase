import { Component }    from 'angular2/core';
import { NgForm }       from 'angular2/common';
import { Router }       from 'angular2/router';

@Component({
    selector: 'my-add-coin',
    templateUrl: 'app/add-coin.component.html'
})

export class AddCoinComponent {
        
    constructor(
        private _router: Router
    ){ }
    
}
