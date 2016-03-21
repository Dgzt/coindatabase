import { Component }    from 'angular2/core';
import { NgForm }       from 'angular2/common';

import { CountryService } from './country.service';
import { Country }      from './country';

@Component({
    selector: 'my-add-country',
    templateUrl: 'app/add-country.component.html'
})

export class AddCountryComponent {
    
    model : Country = {name: ''};
    
        constructor(
        private _countryService : CountryService
    ){ }
    
    onSubmit() {
        this._countryService.save(this.model).subscribe((res: Country) => this.model = res);
    }
}
