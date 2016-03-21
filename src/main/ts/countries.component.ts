import { Component, OnInit } from 'angular2/core';
import { Router } from 'angular2/router';

import { Country } from './country';
import { CountryService } from './country.service';

@Component({
    selector: 'my-countries',
    templateUrl: 'app/countries.component.html'
})

export class CountriesComponent implements OnInit {
        
    countries : Country[];

    constructor(
        private _router: Router,
        private _countryService : CountryService
    ){ }
    
    getCountries(){
        this._countryService.getCountries().then( countries => this.countries = countries );
    }
    
    ngOnInit(){
        this.getCountries();
    }
    
    gotoAddCountry() {
        this._router.navigate(['AddCountry']);
    }
}
