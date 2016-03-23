import { Component }    from 'angular2/core';
import { NgForm }       from 'angular2/common';
import { Router } from 'angular2/router';

import { CountryService } from './country.service';
import { Country }      from './country';

@Component({
    selector: 'my-add-country',
    templateUrl: 'app/add-country.component.html'
})

export class AddCountryComponent {
    
    model : Country = {name: ''};
    
    constructor(
        private _router: Router,
        private _countryService : CountryService
    ){ }
    
    /**
     * Go to countries page.
     */
    gotoCountries(){
        this._router.navigate(['Countries']);
    }
    
    /**
     * When the country is successfully save then return go to countries page.
     */
    onSubmit() {
        this._countryService.save(this.model).subscribe((res: Country) => {
            this.gotoCountries();
        });
    }
}
