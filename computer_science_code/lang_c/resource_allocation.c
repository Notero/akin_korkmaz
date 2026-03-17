//
//  main.c
//  MIA
//
//  Created by Akin Korkmaz on 8/28/24.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct for a material needed by a role.
// We temporarily store the material name here for mapping.
struct mag_mat_for_role {
    char *mat_name;   // temporary; later freed after mapping
    int type;         // index into the global material list (set later)
    long long amount_needed;
};

// Struct for a role.
struct role {
    int materials_needed;                 // number of items for this role
    struct mag_mat_for_role *item_list;   // array of required materials for this role
};

// Struct for a material (global list).
struct mag_mat_for_list {
    char *mat_name;              // material name (dynamically allocated)
    long long total_amount_needed; // sum over all roles (each multiplied by role count)
    long long magic_required;      // magic requirement per unit of this material
};

int main(void) {
    
    int N;
    
    if (scanf("%d", &N) != 1) {
        return 1;
    }
    
    // Allocate roles array.
    struct role *roles = malloc(sizeof(struct role) * N);
    if (!roles) exit(1);
    
    // For each role, read its number of required materials and the list of (material, amount) pairs.
    for (int i = 0; i < N; i++) {
        int Ki;
        if (scanf("%d", &Ki) != 1) exit(1);
        roles[i].materials_needed = Ki;
        roles[i].item_list = malloc(sizeof(struct mag_mat_for_role) * Ki);
        if (!roles[i].item_list) exit(1);
        for (int j = 0; j < Ki; j++) {
            char temp[105];
            int amt;
            if (scanf("%s %d", temp, &amt) != 2) exit(1);
            // Duplicate the string so we can later match with the global material list.
            roles[i].item_list[j].mat_name = strdup(temp);
            roles[i].item_list[j].amount_needed = amt;
            // 'type' will be determined later.
            roles[i].item_list[j].type = -1;
        }
    }
    
    // --- Read the global list of magical materials ---
    // The list is given as a single line of token pairs: <material_name> <magic_required>
    // Use a loop that reads until a newline.
    int materialsCapacity = 10;
    int num_materials = 0;
    struct mag_mat_for_list *materials = malloc(sizeof(struct mag_mat_for_list) * materialsCapacity);
    if (!materials) exit(1);
    
    char buf[105];
    int magic;
    // Consume any leftover newline
    int ch = getchar();
    while (ch == ' ' || ch == '\n') ch = getchar();
    ungetc(ch, stdin);
    
    while (scanf("%s", buf) == 1) {
        if (scanf("%d", &magic) != 1) break;
        // Expand materials array if needed.
        if (num_materials >= materialsCapacity) {
            materialsCapacity *= 2;
            materials = realloc(materials, sizeof(struct mag_mat_for_list) * materialsCapacity);
            if (!materials) exit(1);
        }
        materials[num_materials].mat_name = strdup(buf);
        materials[num_materials].magic_required = magic;
        materials[num_materials].total_amount_needed = 0;
        num_materials++;
        
        // Read next character to check if we've reached the end of the line.
        ch = getchar();
        if(ch == '\n' || ch == EOF)
            break;
        else
            ungetc(ch, stdin);
    }
    
    // --- Read denizens and count how many have each role ---
    int D;
    if (scanf("%d", &D) != 1) exit(1);
    int *role_count = calloc(N, sizeof(int));
    if (!role_count) exit(1);
    for (int i = 0; i < D; i++) {
        int r;
        if (scanf("%d", &r) != 1) exit(1);
        // roles are 1-indexed in input; convert to 0-index.
        role_count[r - 1]++;
    }
    
    // --- Map role items to global material indices ---
    // For each role's required material, find its index in the materials list.
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < roles[i].materials_needed; j++) {
            char *name = roles[i].item_list[j].mat_name;
            int found = -1;
            for (int k = 0; k < num_materials; k++) {
                if (strcmp(materials[k].mat_name, name) == 0) {
                    found = k;
                    break;
                }
            }
            roles[i].item_list[j].type = found;
            // Free the temporary string as it’s no longer needed in the role.
            free(name);
            roles[i].item_list[j].mat_name = NULL;
        }
    }
    
    // --- Compute total required amounts per material ---
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < roles[i].materials_needed; j++) {
            int midx = roles[i].item_list[j].type;
            // Multiply the role's need by the number of denizens with that role.
            materials[midx].total_amount_needed += roles[i].item_list[j].amount_needed * (long long) role_count[i];
        }
    }
    
    // --- Compute the initial global magic total ---
    long long global_total = 0;
    for (int i = 0; i < num_materials; i++) {
        global_total += materials[i].total_amount_needed * materials[i].magic_required;
    }
    
    // --- Process updates ---
    int U;
    if (scanf("%d", &U) != 1) exit(1);
    for (int i = 0; i < U; i++) {
        int update_type;
        if (scanf("%d", &update_type) != 1) exit(1);
        if (update_type == 1) {
            // Update format: "1 m x" - change magic requirement of material m to x.
            char mname[105];
            int new_magic;
            if (scanf("%s %d", mname, &new_magic) != 2) exit(1);
            int midx = -1;
            for (int k = 0; k < num_materials; k++) {
                if (strcmp(materials[k].mat_name, mname) == 0) {
                    midx = k;
                    break;
                }
            }
            if(midx == -1) continue;  // should not occur based on problem guarantees
            
            int old_magic = materials[midx].magic_required;
            long long diff = (long long)(new_magic - old_magic) * materials[midx].total_amount_needed;
            global_total += diff;
            materials[midx].magic_required = new_magic;
            printf("%lld\n", global_total);
        }
        else if (update_type == 2) {
            // Update format: "2 r m a" - role r now needs a amount of material m.
            int r;
            char mname[105];
            int new_amount;
            if (scanf("%d %s %d", &r, mname, &new_amount) != 3) exit(1);
            int role_index = r - 1;
            int found_item = -1;
            int midx = -1;
            // Search the role's list for material m.
            for (int j = 0; j < roles[role_index].materials_needed; j++) {
                int t = roles[role_index].item_list[j].type;
                // Compare with the global material name.
                if (strcmp(materials[t].mat_name, mname) == 0) {
                    found_item = j;
                    midx = t;
                    break;
                }
            }
            if (found_item == -1) continue;  // should not occur
            
            long long old_amount = roles[role_index].item_list[found_item].amount_needed;
            long long delta = new_amount - old_amount;
            
            // The change in global magic is:
            // (delta * (number of citizens with role role_index) * (magic cost for that material)).
            long long diff = delta * role_count[role_index] * materials[midx].magic_required;
            global_total += diff;
            // Update the role's requirement.
            roles[role_index].item_list[found_item].amount_needed = new_amount;
            // Also update the global total for that material.
            materials[midx].total_amount_needed += delta * role_count[role_index];
            printf("%lld\n", global_total);
        }
    }
    
    // --- Clean up ---
    
    for (int i = 0; i < N; i++) {
        free(roles[i].item_list);
    }
    
    free(roles);
    
    for (int i = 0; i < num_materials; i++) {
        free(materials[i].mat_name);
    }
    
    free(materials);
    free(role_count);
    
    return 0;
}
