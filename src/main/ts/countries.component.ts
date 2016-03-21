import { Component, OnInit } from 'angular2/core';

import { Country } from './country';
import { CountryService } from './country.service';

@Component({
    selector: 'my-countries',
    templateUrl: 'app/countries.component.html',
    providers: [ CountryService ]
})

export class CountriesComponent implements OnInit {
        
    countries : Country[];

    constructor(private _countryService : CountryService){ }
    
    getCountries(){
        this._countryService.getCountries().then( countries => this.countries = countries );
    }
    
    ngOnInit(){
        this.getCountries();
    }
}
