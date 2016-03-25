import {Component}  from 'angular2/core';
import { Router }   from 'angular2/router';

@Component({
    selector: 'my-coins',
    templateUrl: 'app/coins.component.html'
})

export class CoinsComponent {
        
    constructor(
        private _router: Router
    ){ }

    gotoAddCoin() {
        this._router.navigate(['AddCoin']);
    }
}
