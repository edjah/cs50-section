// Small vector library
function Vector(x, y, z) {
    this.x = x === undefined ? 0 : x;
    this.y = y === undefined ? 0 : y;
    this.z = z === undefined ? 0 : z;

    this.add = function(u, c) {
        c = c === undefined ? 1 : c;
        return new Vector(this.x + u.x * c, this.y + u.y * c, this.z + u.z * c);
    }

    this.subtract = function(u, c) {
        c = c === undefined ? 1 : c;
        return new Vector(this.x - u.x * c, this.y - u.y * c, this.z - u.z * c);
    }

    this.magnitude = function() {
        let sum = (this.x * this.x) + (this.y * this.y) + (this.z * this.z);
        return Math.sqrt(sum);
    }

    this.dist = function(u) {
        return this.subtract(u).magnitude();
    }

    this.dot = function(u) {
        return (this.x * u.x) + (this.y * u.y) + (this.z * u.z);
    }

    this.normalize = function() {
        let mag = this.magnitude() || Infinity;
        return new Vector(this.x / mag, this.y / mag, this.z / mag);
    }

    this.mult = function(c) {
        return new Vector(this.x * c, this.y * c, this.z * c);
    }

    this.get = function() {
        return new Vector(this.x, this.y, this.z);
    }

    this.round = function() {
        return new Vector(
            Math.round(this.x * 100) / 100,
            Math.round(this.y * 100) / 100,
            Math.round(this.z * 100) / 100
        );
    }

    this.project = function(u) {
        //Project ONTO u
        return u.mult(this.dot(u) / u.dot(u));
    }
}

// Important global variables for assigning a velocity vector
let p1 = new Vector(0, 0);
let p2 = new Vector(0, 0);
let velocityToAssign = new Vector(0, 0);
let velocityVectorActive = false;


// Other important Global variables
let G = 1;                      // Universal Gravitation Constant
let K = 0;                      // Coulomb's Constant
let simSpeed = 1;               // Speed of the simulation
let particleMass = 400;         // Mass of a new particle
let numUniqueParticles = 0;     // Constantly increasing unique number
let targetFrameRate = 60;       // Target FPS for the animation
let list = [];                  // List of all particles in system


// Object definition for a particle
function Particle(htmlID, px, py, vx, vy, mass) {
    this.htmlID = htmlID;
    this.position = new Vector(px, py);
    this.velocity = new Vector(vx, vy);
    this.netForce = new Vector(0, 0);
    this.mass = mass;
    this.momentum = this.velocity.mult(this.mass);
    this.radius = Math.sqrt(this.mass);

    this.update = function() {
        let acceleration = this.netForce.mult(1 / this.mass);
        this.velocity = this.velocity.add(acceleration, simSpeed);
        this.momentum = this.velocity.mult(this.mass);
        this.position = this.position.add(this.velocity, simSpeed);
        $(this.htmlID).css({
            "r": this.radius,
            "cx": this.position.x,
            "cy": this.position.y
        });

    };
};


// Function for handling velocity vector creation
function velocityVector() {
    $("#canvas").mousemove(function(event) {
        if (event.which === 1 && velocityVectorActive) {
            p2.x = event.pageX;
            p2.y = event.pageY;
            velocityToAssign.x = p2.x - p1.x;
            velocityToAssign.y = p2.y - p1.y;
            velocityToAssign = velocityToAssign.mult(1 / 30);
            $("#line").attr({
                "x1": p1.x,
                "y1": p1.y,
                "x2": p2.x,
                "y2": p2.y,
                "display": "inline"
            });
        }
    })
};


$("#canvas").mousedown(function(event) {
    if (event.which === 1) {
        p1.x = event.pageX;
        p1.y = event.pageY;
        velocityVectorActive = true;
        velocityVector();
    }
});


$("#canvas").mouseup(function() {
    if (velocityVectorActive) {
        velocityVectorActive = false;
        $("#line").attr("display", "none");
        createParticle(p1, velocityToAssign, particleMass);
        velocityToAssign = new Vector(0, 0);
        p1 = new Vector(0, 0);
        p2 = new Vector(0, 0);
    }
});


// Update the simulation speed based on the slider's value
$("#simspeed").on("input", function() {
    simSpeed = this.value / 20;
});



// construct a new particle
function createParticle(p, v, mass) {
    let newTag = document.createElementNS("http://www.w3.org/2000/svg", 'circle');
    let newTagId = "particle" + numUniqueParticles;
    newTag.setAttribute("id", newTagId);

    let rgb = [0, 0, 0].map(() => Math.floor(Math.random() * (255 - 75)) + 75);
    let colorString = "rgb(" + rgb.join(",") + ")";

    $("#canvas").append(newTag);
    $("#" + newTagId).css({
        "cx": p.x,
        "cy": p.y,
        "r": Math.sqrt(mass),
        "fill": colorString
    });

    list.push(new Particle("#" + newTagId, p.x, p.y, v.x, v.y, mass));
    numUniqueParticles++;

    return list[list.length - 1];
};


// calculate gravitational forces
function calculateForces() {
    //This zeros out the forces on each object before the loop
    for (let i = 0; i < list.length; i++) {
        list[i].netForce.x = 0;
        list[i].netForce.y = 0;
    }

    //This calculates the gravitational forces that each particle experiences
    for (let i = 0; i < list.length; i++) {
        for (let j = i + 1; j < list.length; j++) {
            if (typeof list[i] !== 'undefined' && typeof list[j] !== 'undefined') {
                let displacement = list[i].position.subtract(list[j].position);
                let direction = displacement.normalize();
                if (displacement.magnitude() > list[i].radius + list[j].radius) {
                    let distSquared = Math.pow(displacement.magnitude(), 2);
                    let forceMagnitude = (G * list[i].mass * list[j].mass) / distSquared;
                    list[i].netForce = list[i].netForce.subtract(direction.mult(forceMagnitude));
                    list[j].netForce = list[j].netForce.add(direction.mult(forceMagnitude));
                }
            }
        }
    }
};

// detect collisions
function collisionDetection() {
    for (let i = 0; i < list.length - 1; i++) {
        for (let j = i + 1; j < list.length; j++) {
            let displacement = list[i].position.subtract(list[j].position);
            if (displacement.magnitude() < list[i].radius + list[j].radius) {
                list[i].momentum = list[i].momentum.add(list[j].momentum);
                list[i].mass += list[j].mass;
                list[i].radius = Math.sqrt(list[i].mass);
                list[i].velocity = list[i].momentum.mult(1 / list[i].mass);
                $(list[j].htmlID).remove();
                list.splice(j, 1);
            }
        }
    }
}

// Tracking framerate
let fpsCounter = document.getElementById("fpscounter");
let fps = {
    startTime: 0,
    frameNumber: 0,
    getFPS: function() {
        this.frameNumber++;
        let d = new Date().getTime(),
        currentTime = (d - this.startTime) / 1000,
        result = Math.floor(this.frameNumber / currentTime);
        if (currentTime > 1) {
            this.startTime = new Date().getTime();
            this.frameNumber = 0;
        }
        return result;
    }
};


// Calculates forces, collisions, and renders a frame
function drawFrame() {
    calculateForces();
    for (let i = 0; i < list.length; i++) {
        list[i].update();
    }
    collisionDetection();
};

// The actual animation
let animation = setInterval(function() {
    drawFrame();
    fpsCounter.innerHTML = "FPS: " + fps.getFPS();
}, 1000 / targetFrameRate);
