var frozen = document.querySelector('#frozen');
var chimera = document.querySelector('#chimera');
var follow = document.querySelector('#follow');
var sun = document.querySelector('#sun');
var iodine = document.querySelector('#iodine');
var chemist = document.querySelector('#chemist');
var close = document.querySelector('#close');
var paranoia = document.querySelector('#paranoia');
var uncle = document.querySelector('#uncle');
var tracks = [frozen, chimera, follow, sun, iodine, chemist, close, paranoia, uncle];
for (let t of tracks) {
	t.onplay = function() {
		for (let o of tracks) {
			if (o != t)
				o.pause();
		}
	}
}
for (let i = 0; i < tracks.length; ++i) {
	if (i < tracks.length - 1) {
		const nexttrack = tracks[i + 1];
		tracks[i].onended = function() { nexttrack.play(); }
	}
}
