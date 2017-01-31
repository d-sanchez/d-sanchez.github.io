/*ini_set('display_errors',1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);
*/
$(document).ready(function(){
    
    // initial
    $('#content').load('content/index.php');

    // handle menu clicks
    $('ul#nav a').click(function(){
        var page = $(this).attr('href');

	var re = new RegExp("^(http|https|mailto):", "i");
	if (re.test(page)){
	    // alert("test");
	    return true;
	} else {
            $('#content').load('content/' + page + '.php');        
	}

	// when you decide not to be lazy anymore look this up
        return false;
    });
});