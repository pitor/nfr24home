rkvApp.config(['$routeProvider', function($routeProvider) {
    $routeProvider.
	when('/', {
	    templateUrl: 'views/sensors.html',
	    controller: 'SensorsController'
	}).
	otherwise({
	    redirectTo: '/'
	});
}]);