rkvApp.controller('SensorsController', [ '$scope', 'RPCService', function( $scope, rpc ) {
    $scope.hest = "HEST";

    $scope.values = [];
    rpc.getVals().then(
	function( result ) {
	    console.log("Got result");
	},
	function( error ) {
	    console.log("Got error");
	}
    );

}]);
